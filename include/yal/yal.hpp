#ifndef _yal_hpp_INClude__
#define _yal_hpp_INClude__
#include <algorithm>
#include <memory>
#include <string_view>
#include <vector>
#include <yal/log_level.h>
#include <yal/sinks/console_sink.h>
#include <yal/sinks/empty_sink.h>
#include <yal/yal_export.h>

namespace yalog {
/**
 * @brief Class representing different types of encoding to be able to convert
 * text to different encoding.
 *
 */
enum class character_encoding : int {
  ascii = 7,
  ansii = 8,
  codepage1252 = 8,
  utf8 = 8 * 8,
  utf16 = 16 * 8,
  utf32 = 32 * 8,
};
using char_enc = character_encoding;
/**
 * @brief Stream ending in a sink, it will issue a log message everytime it
 * reads an newline character.
 *
 */
class EXPORT_YAL_API logger_stream {
private:
  std::unique_ptr<sink> m_sink;

public:
  /**
   * @brief Construct a new logger stream with a sink.It will emit a log message
   * if the object deconstructs or a newline character is read.
   *
   * @todo Rethink ownership of a sink
   * @todo make it private
   *
   * @param sink new sink this logger_stream owns
   */
  logger_stream(std::unique_ptr<sink> &&sink) : m_sink{std::move(sink)} {}
#pragma region stream operators
  /**
   * @brief Writing a Log Message via stream operator. It will emit a log
   * message if the object deconstructs or a newline character is read.
   * If the current encoding is larger then sizeof(char) it will throw.
   * (UTF16/32)
   *
   * @param msg Log message to write. Assumed encoding is utf-8, until changed.
   * @return logger_stream& for chaining purpose
   */
  logger_stream &operator<<(const std::string_view &msg);
  /**
   * @brief Writing a Log message via stream operator. It will emit a log
   * message if the object is deconstructed or a newline character is read.
   * If the current encoding is larger then sizeof(wchar_t) it will throw.
   *
   * @param msg Log message to write. Its assumed encoding is utf-16, until
   * changed.
   * @return logger_stream& for chaining purpose
   */
  logger_stream &operator<<(const std::wstring_view &msg);
  /**
   * @brief Method to change the encoding of the stream operators to a different
   * encoding. If the encoding is unkown it will throw.
   *
   * @param new_encoding new encoding to set for the following streaming
   * operators
   * @return logger_stream& for chaining purpose
   */
  logger_stream &operator<<(character_encoding new_encoding);
#pragma endregion
#pragma region print char
  /**
   * @brief Prints a Message to the log, will append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called.
   *
   * @tparam args Argument pack for multiple arguments.
   * @param msg Message to print. Style like printf.
   * @param enc Encoding to use, it will throw if the encoding is larger then
   * sizeof(char). For example UTF16/32
   * @param arguments Template Pack to pass values to replace printf special
   * characters. For Example: println("%x", ansii, 5);
   */
  template <typename... args>
  void println(const std::string_view &msg, character_encoding enc,
               const args &... arguments);

  /**
   * @brief Prints a Message to the log, will NOT append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called.
   *
   * @tparam args Argument pack for multiple arguments.
   * @param msg Message to print. Style like printf.
   * @param enc Encoding to use, it will throw if the encoding is larger then
   * sizeof(char). For example UTF16/32
   * @param arguments Template Pack to pass values to replace printf special
   * characters. For Example: println("%x", ansii, 5);
   */
  template <typename... args>
  void print(const std::string_view &msg, character_encoding enc,
             const args &... arguments);

  /**
   * @brief Prints a Message to the log, will append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called. Encoding depends on which OS is used: Windows = codepage 1252,
   * Linux = UTF8
   *
   * @tparam args Argument pack for multiple arguments.
   * @param msg Message to print. Style like printf.
   * @param arguments Template Pack to pass values to replace printf special
   * characters. For Example: println("%x", 5);
   */
  template <typename... args>
  void println(const std::string_view &msg, const args &... arguments);
  /**
   * @brief Prints a Message to the log, will NOT append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called. Encoding depends on which OS is used: Windows = codepage 1252,
   * Linux = UTF8
   *
   * @tparam args Argument pack for multiple arguments.
   * @param msg Message to print. Style like printf.
   * @param arguments Template Pack to pass values to replace printf special
   * characters. For Example: println("%x", 5);
   */
  template <typename... args>
  void print(const std::string_view &msg, const args &... arguments);
#pragma endregion
#pragma region print wchar
  /**
   * @brief Prints a Message to the log. It will append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called.
   *
   * @tparam args Argument pack for multiple arguments.
   * @param msg Message to print. Style like printf.
   * @param enc Encoding to use, it will throw if the encoding is larger then
   * sizeof(wchar_t). For example UTF16/32
   * @param arguments Template Pack to pass values to replace printf special
   * characters. For Example: println("%x", ansii, 5);
   */
  template <typename... args>
  void println(const std::wstring_view &msg, character_encoding enc,
               const args &... arguments);

  /**
   * @brief Prints a Message to the log, will NOT append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called.
   *
   * @tparam args Argument pack for multiple arguments.
   * @param msg Message to print. Style like printf.
   * @param enc Encoding to use, it will throw if the encoding is larger then
   * sizeof(wchar_t).
   * @param arguments Template Pack to pass values to replace printf special
   * characters. For Example: println("%x", ansii, 5);
   */
  template <typename... args>
  void print(const std::wstring_view &msg, character_encoding enc,
             const args &... arguments);

  /**
   * @brief Prints a Message to the log, will append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called. Encoding depends on which OS is used: Windows = UTF16,
   * Linux = UTF16
   *
   * @tparam args Argument pack for multiple arguments.
   * @param msg Message to print. Style like printf.
   * @param arguments Template Pack to pass values to replace printf special
   * characters. For Example: println("%x", 5);
   */
  template <typename... args>
  void println(const std::wstring_view &msg, const args &... arguments);
  /**
   * @brief Prints a Message to the log, will NOT append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called. Encoding depends on which OS is used: Windows = UTF16,
   * Linux = UTF16
   *
   * @tparam args Argument pack for multiple arguments.
   * @param msg Message to print. Style like printf.
   * @param arguments Template Pack to pass values to replace printf special
   * characters. For Example: println("%x", 5);
   */

  template <typename... args>
  void print(const std::wstring_view &msg, const args &... arguments);
#pragma endregion
};
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
  logger_stream null_sink{std::make_unique<sinks::empty_sink>()};
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
