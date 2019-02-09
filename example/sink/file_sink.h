#ifndef file_sink_INClude_H
#define file_sink_INClude_H
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

#include <yal/sink.hpp>
/**
 * @brief File Sink, which implements a rotation and different encodings
 *
 */
class file_sink : public yalog::sink {
public:
  file_sink() = delete;
  /**
   * @brief Construct a new file sink object
   *
   * @param log_directory Directory where the files should be written to. If
   * this is not an writeable directory it will throw an std::logic_error
   * @param file_encoding Encoding of the file
   * @param max_file_size Maximum File Size at which the sink should rotate (In
   * Bytes)
   */
  explicit file_sink(std::filesystem::path log_directory,
                     yalog::char_enc file_encoding,
                     std::size_t max_file_size = 0);
  file_sink(const file_sink &) = delete;
  file_sink(file_sink &&) = default;
  file_sink &operator=(const file_sink &) = delete;
  file_sink &operator=(file_sink &&) = default;
  virtual ~file_sink() = default;
  virtual void print(const yalog::log_message &message) override;

  std::filesystem::path directory() const;

private:
  bool is_file_size_to_big(std::filesystem::path file);
  
  std::filesystem::path next_file();
  static constexpr std::string_view log_file = "filelog";
  static constexpr std::string_view file_ending = ".log";
  int current_file {0};
  std::ofstream file_output;
  const std::size_t m_max_file_size;
  const yalog::char_enc m_file_encoding;
  std::filesystem::path m_directory;
};

#endif // file_sink_INClude_H
