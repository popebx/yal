#ifndef _yal_hpp_INClude__
#define _yal_hpp_INClude__
#include <memory>
#include <string_view>
#include <yal/console_sink.h>
#include <yal/empty_sink.h>
#include <yal/yal_export.h>

namespace yalog {
enum class log_level {
  DEBUG,
  WARNING,
  ERROR,
};

template <typename T> class logger_stream {
private:
  T current_sink;

public:
  logger_stream(T &&sink) : current_sink{std::move(sink)} {}

  template <typename T> logger_stream &operator<<(T arg) {
    return this->operator<<(to_yal(arg));
  }
  logger_stream &operator<<(const std::string_view &arg) {
    this->current_sink.print(arg);
    return *this;
  }
  logger_stream &operator<<(const std::wstring_view &arg) {
    this->current_sink.print(arg);
    return *this;
  }
};
template <typename T> std::string_view to_yal(T);

static std::string_view to_yal(const char *arg) {
  return std::string_view{arg};
}

class logger {
private:
  log_level m_log_level;
  logger_stream<yalog::empty_sink> null_sink{};

public:
  logger(log_level arg) : m_log_level{arg} {}
  logger_stream &warn() {
    if (this->m_log_level > log_level::WARNING) {
      this->
    }
  }
  logger_stream &debug() {}
  logger_stream &error() {}
}

} // namespace yalog

#endif //_yal_hpp_INClude__
