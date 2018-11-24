#ifndef _yal_hpp_INClude__
#define _yal_hpp_INClude__
#include <algorithm>
#include <memory>
#include <string_view>
#include <vector>
#include <yal/log_level.h>
#include <yal/sink_queue.hpp>
#include <yal/sinks/console_sink.h>
#include <yal/sinks/empty_sink.h>
#include <yal/yal_export.h>
#include <yal/yal_stream.hpp>

namespace yalog {

/**
 * @brief Specialize this template function to being able to print your Datatype
 * to the streaming operators.
 *
 * @todo remove cv
 *
 * @tparam type typename of your object
 * @return std::string stringfied object
 */
template <typename type> std::string to_yal(type);
class logger {
private:
  log_level m_log_level;
  logger_stream null_sink{sinks::empty_sink>()};
  logger_stream current_sink;

public:
  /**
   * @brief
   *
   * @todo Make it private
   *
   * @param arg
   */
  logger(log_level arg)
      : m_log_level{arg}, current_sink{std::make_unique<sinks::console_out>()} {
  }

  /**
   * @brief Returns a stream taking a new warning log message
   *
   * @return logger_stream& Stream to log your warning message
   */
  logger_stream &warn() {
    if (this->m_log_level < log_level::WARNING) {
      return this->current_sink;
    }
    return null_sink;
  }
  /**
   * @brief Returns a stream taking a new debug log message
   *
   * @return logger_stream& Stream to log your debug message
   */
  logger_stream &debug() {
    if (this->m_log_level < log_level::DEBUG) {
      return this->current_sink;
    }
    return null_sink;
  }

  /**
   * @brief Returns a stream taking a new error log message
   *
   * @return logger_stream& Stream to your error message
   */
  logger_stream &error() {
    if (this->m_log_level < log_level::ERROR) {
      return this->current_sink;
    }
    return this->null_sink;
  }
};

} // namespace yalog

#endif //_yal_hpp_INClude__
