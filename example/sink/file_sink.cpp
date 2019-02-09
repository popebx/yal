#include "file_sink.h"

file_sink::file_sink(std::filesystem::path log_directory,
                     yalog::char_enc file_encoding, std::size_t max_file_size)
    : m_max_file_size{max_file_size}, m_file_encoding{file_encoding},
      m_directory{log_directory} {}

void file_sink::print(const yalog::log_message &message) {}