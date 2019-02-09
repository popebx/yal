#ifndef file_sink_INClude_H
#define file_sink_INClude_H
#include <filesystem>
#include <yal/sink.hpp>

class file_sink : public yalog::sink {
public:
  file_sink() = delete;
  explicit file_sink(std::filesystem::path log_directory, yalog::char_enc file_encoding,
                     std::size_t max_file_size = 0);
  file_sink(const file_sink &) = delete;
  file_sink(file_sink &&) = default;
  file_sink &operator=(const file_sink &) = delete;
  file_sink &operator=(file_sink &&) = default;
  virtual ~file_sink() = default;
  virtual void print(const yalog::log_message &message) override;

  std::filesystem::path directory() const;

private:
  const std::size_t m_max_file_size;
  const yalog::char_enc m_file_encoding;
  const std::filesystem::path m_directory;
};

#endif // file_sink_INClude_H
