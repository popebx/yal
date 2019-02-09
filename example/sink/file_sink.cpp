#include "file_sink.h"
#include <string>
#include <sstream>
#include "helper_functions.h"


file_sink::file_sink(std::filesystem::path log_directory, yalog::char_enc file_encoding, std::size_t max_file_size)
    : m_max_file_size{max_file_size}, m_file_encoding{file_encoding}, m_directory{}, file_output{} {
  log_directory = std::filesystem::absolute(log_directory);
  if (!std::filesystem::is_directory(log_directory) && !std::filesystem::create_directory(log_directory)) {
    throw std::logic_error("Not a valid directory");
  }

  this->m_directory = log_directory;
  this->file_output.open(next_file(), std::ios::ate | std::ios::binary);
}


std::string format_message(const yalog::log_message & message) {
  std::stringstream formatted_string{};
  formatted_string << "[" << conversion::as_ascii(message.level) << "] - "
                   << std::put_time(std::localtime(&message.timestamp), "%Y-%m-%d %X")
                   << " (Thread ID: " << message.thread_id << "): ";
  return formatted_string.str();
}

void file_sink::print(const yalog::log_message& message) {
  if (!this->file_output.is_open()) {
    throw std::logic_error("Can't write File");
  }
  if (message.encoding == this->m_file_encoding) {
    std::string buf = format_message(message);
    this->file_output.write(buf.c_str(), buf.size());
    for (uint8_t chr : message.message) {
      this->file_output.write(reinterpret_cast<const char*>(message.message.data()), message.message.size());
    }
  } else {
    if (message.encoding == yalog::char_enc::ascii &&
        (m_file_encoding == yalog::char_enc::utf8 || m_file_encoding == yalog::char_enc::ascii)) {
      std::string buf = format_message(message);
      this->file_output.write(buf.c_str(), buf.size());
      for (uint8_t chr : message.message) {
        this->file_output.write(reinterpret_cast<const char*>(message.message.data()), message.message.size());
      }
    } else {
      // No Conversion implemented  
	}
  }
  
}

bool file_sink::is_file_size_to_big(std::filesystem::path file) {
  return std::filesystem::exists(file) && std::filesystem::file_size(file) > this->m_max_file_size &&
         this->m_max_file_size != 0;
}

std::filesystem::path file_sink::next_file() {
  int i = 0;
  while (i >= 0) {
    std::filesystem::path buffer = this->m_directory;
    std::string file_name{file_sink::log_file};
    file_name += std::to_string(i) + file_sink::file_ending.data();

    buffer /= file_name;
    if (!is_file_size_to_big(buffer)) {
      return buffer;
    };
    i++;
  }
  throw std::logic_error("No file can be created");
}