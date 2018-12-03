#ifndef _yal_hpp_INClude__
#define _yal_hpp_INClude__
#include <yal/log_level.hpp>
#include <yal/dll_export.h>
#include <algorithm>
#include <memory>
#include <string_view>
#include <vector>
#include <yal/stream.hpp>


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
template <typename type>
std::string to_yal(type);
class EXPORT_YAL_API logger {
 private:
  log_level m_log_level;
  ystream null_stream{};
  sync_sink_queue* current_sink;

 public:
  /**
   * @brief
   *
   * @todo Make it private
   *
   * @param arg
   */
  logger(log_level arg, sync_sink_queue* ref_sink);

  /**
   * @brief Returns a stream taking a new warning log message
   *
   * @return logger_stream& Stream to log your warning message
   */
  ystream warn();
  /**
   * @brief Returns a stream taking a new debug log message
   *
   * @return logger_stream& Stream to log your debug message
   */
  ystream debug();

  /**
   * @brief Returns a stream taking a new error log message
   *
   * @return logger_stream& Stream to your error message
   */
  ystream error();
};

}  // namespace yalog

#endif  //_yal_hpp_INClude__
