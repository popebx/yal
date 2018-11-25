#include <chrono>
#include <thread>
#include <yal/yal_stream.hpp>

namespace yalog {

#if defined(_WIN32) || defined(_WIN64)
using wchar_type = char16_t;
using wchar_string = std::u16string;
using wchar_string_view = std::u16string_view;
#else
using wchar_type = char32_t;
using wchar_string = std::u32string;
using wchar_string_view = std::u32string_view;
#endif

log_message ystream::create_new_message() {
  log_message new_msg;
  new_msg.thread_id = std::this_thread::get_id();
  new_msg.timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  new_msg.level = this->m_current_level;
  new_msg.encoding = this->m_current_encoding.value();
  return new_msg;
}

ystream::~ystream() {
  if (!this->m_current_message.empty() && this->m_sink != nullptr) {
    log_message new_msg = this->create_new_message();
    if (this->m_current_encoding == char_enc::utf16) {
      this->m_current_message.emplace_back(0x0);
    } else if (this->m_current_encoding == char_enc::utf32) {
      this->m_current_message.emplace_back(0x0);
      this->m_current_message.emplace_back(0x0);
      this->m_current_message.emplace_back(0x0);
    }
    this->m_current_message.emplace_back(0xA);
    new_msg.message = this->m_current_message;
    this->m_sink->push(std::move(new_msg));
  }
}

ystream::ystream(log_level current_level, sync_sink_queue* sink) : m_sink{sink}, m_current_level(current_level) {}
#pragma region Overload set append_message
void ystream::append_message(const std::string_view& new_message, char_enc encoding) {
  if (this->m_sink != nullptr) {
    if (this->m_current_encoding.value_or(encoding) == encoding) {
      this->m_current_encoding = encoding;
      std::transform(new_message.begin(), new_message.end(), std::back_inserter(this->m_current_message),
                     [](const char current_char) { return static_cast<uint8_t>(current_char); });

      bool contains_newline = false;
      do {
        auto result = std::find_if(this->m_current_message.begin(), this->m_current_message.end(), [](const uint8_t c) { return c == 0xA; });
        contains_newline = result != this->m_current_message.end();
        if (contains_newline) {
          log_message new_msg = create_new_message();

          new_msg.message = {this->m_current_message.begin(), result + 1};
          this->m_sink->push(std::move(new_msg));
          this->m_current_message.erase(this->m_current_message.begin(), result + 1);
        }
      } while (contains_newline);
    }
  }
}
void ystream::append_message(const std::u16string_view& new_message, char_enc encoding) {
  if (this->m_sink != nullptr) {
    if (this->m_current_encoding.value_or(encoding) == encoding) {
      this->m_current_encoding = encoding;
    }
  }
}

void ystream::append_message(const std::u32string_view& new_message, char_enc encoding) {
  if (this->m_sink != nullptr) {
    if (this->m_current_encoding.value_or(encoding) == encoding) {
      this->m_current_encoding = encoding;
    }
  }
}
#pragma endregion
#pragma region Overload set operator<<
ystream& ystream::operator<<(const std::string_view& msg) {
  this->print(msg, char_enc::codepage1252);
  return *this;
}

ystream& ystream::operator<<(const std::u16string_view& msg) {
  this->operator<<(char_enc::utf16);
  this->print(msg);
  return *this;
}
ystream& ystream::operator<<(const std::u32string_view& msg) {
  this->operator<<(char_enc::utf32);
  this->print(msg);
  return *this;
}

ystream& ystream::operator<<(const std::wstring_view& msg) {
  this->print(msg);
  return *this;
}
#pragma endregion
ystream& ystream::operator<<(character_encoding new_encoding) {
  if (this->m_current_message.empty() || this->m_current_encoding.value_or(new_encoding) == new_encoding) {
    this->m_current_encoding = new_encoding;
    return *this;
  }
  throw std::runtime_error("Can't set encoding on a used buffer!");
}

void ystream::println(const std::string_view& msg, character_encoding enc) {
  this->append_message(msg, enc);
}
void ystream::print(const std::string_view& msg, character_encoding enc) {
  this->append_message(msg, enc);
}
void ystream::println(const std::string_view& msg) {
  this->append_message(msg, char_enc::codepage1252);
}

void ystream::println(const std::u16string_view& msg) {
  this->append_message(msg, char_enc::codepage1252);
}
void ystream::println(const std::u32string_view& msg) {
  this->append_message(msg, char_enc::codepage1252);
}

void ystream::print(const std::string_view& msg) {
  this->append_message(msg, char_enc::codepage1252);
}
void ystream::print(const std::u16string_view& msg) {
  this->append_message(msg, char_enc::codepage1252);
}
void ystream::print(const std::u32string_view& msg) {
  this->append_message(msg, char_enc::codepage1252);
}
void ystream::println(const std::wstring_view& msg) {
  wchar_string temp;
  temp.reserve(msg.size());
  std::transform(msg.begin(), msg.end(), std::back_inserter(temp), [](wchar_t c) { return static_cast<wchar_type>(c); });
  this->println(temp);
}
void ystream::print(const std::wstring_view& msg) {
  wchar_string temp;
  temp.reserve(msg.size());
  std::transform(msg.begin(), msg.end(), std::back_inserter(temp), [](wchar_t c) { return static_cast<wchar_type>(c); });
  this->println(temp);
}
}  // namespace yalog