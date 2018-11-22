#ifndef _sink_h_INClude
#define _sink_h_INClude
#include <string_view>

namespace yalog {

/**
 * @brief Sink Interface Definition. A sink will get called on print when a new
 * log message is received. It handles writing the Message to std::cout/file
 * etc.
 *
 */
class sink {
public:
  /**
   * @brief Prints a new log message. Will get called when a new log message
   * arrives.
   *
   * @todo Encoding?
   *
   * @param msg new message
   */
  virtual void print(const std::string_view &msg) = 0;
  /**
   * @brief Prints a new log message. Will get called when a new log message
   * arrives.
   *
   * @todo Encoding?
   *
   * @param msg new message
   */
  virtual void print(const std::wstring_view &) = 0;
  virtual ~sink() = default;
};
} // namespace yalog
#endif //_sink_h_INClude
