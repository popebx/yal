#ifndef yal_stream_h_INClude
#define yal_stream_h_INClude
#include <yal/yal_export.h>
#include <optional>
#include <yal/sink_queue.hpp>

namespace yalog {

/**
 * @brief Stream ending in a sink, it will issue a log message everytime it
 * reads an newline character.
 *
 */
class EXPORT_YAL_API ystream {
 private:
  sync_sink_queue* m_sink = nullptr;

  std::optional<character_encoding> m_current_encoding;
  std::vector<uint8_t> m_current_message;

  log_level m_current_level;

  log_message create_new_message();
  void append_message(const std::string_view& new_message, char_enc encoding);
  void append_message(const std::u16string_view& new_message, char_enc encoding);
  void append_message(const std::u32string_view& new_message, char_enc encoding);

 public:
  ystream() = default;
  ~ystream();
  /**
   * @brief Construct a new logger stream with a sink.It will emit a log message
   * if the object deconstructs or a newline character is read.
   *
   * @todo Rethink ownership of a sink
   * @todo make it private
   *
   * @param sink new sink this logger_stream owns
   */
  ystream(log_level current_level, sync_sink_queue* sink);
#pragma region stream operators
  /**
   * @brief Writing a Log Message via stream operator. It will emit a log
   * message if the object deconstructs or a newline character is read.
   * If the encoding is changed during Object Lifetime it will throw!
   *
   * @param msg Log message to write. Assuming ANSII for std::string_view until c++20 then u8 will be added hopefully
   * @return ystream& for chaining purpose
   */
  ystream& operator<<(const std::string_view& msg);
  ystream& operator<<(const std::u16string_view& msg);
  ystream& operator<<(const std::u32string_view& msg);
  /**
   * @brief Writing a Log Message via stream operator. It will emit a log
   * message if the object deconstructs or a newline character is read.
   * If the encoding is changed during Object Lifetime it will throw!
   *
   * @param msg Log message to write. Its assumed encoding is utf-16 with windows else utf-32
   * @return ystream& for chaining purpose
   */
  ystream& operator<<(const std::wstring_view& msg);
  /**
   * @brief Method to change the encoding of the stream operators to a different
   * encoding.
   * If the encoding is changed during Object Lifetime it will throw, unless nothing is written into it!
   *
   * @param new_encoding new encoding to set for the following streaming
   * operators
   * @return ystream& for chaining purpose
   */
  ystream& operator<<(character_encoding new_encoding);
#pragma endregion
#pragma region print char
  /**
   * @brief Prints a Message to the log, will append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called.
   * If the encoding is changed during Object Lifetime it will throw!
   *
   * @param msg Message to print.
   * @param enc Encoding to use, it will throw if the encoding is larger then
   * sizeof(char). For example UTF16/32
   */
  void println(const std::string_view& msg, character_encoding enc);

  /**
   * @brief Prints a Message to the log, will NOT append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called.
   * If the encoding is changed during Object Lifetime it will throw!
   *
   * @param msg Message to print.
   * @param enc Encoding to use, it will throw if the encoding is larger then
   * sizeof(char). For example UTF16/32
   
   */
  void print(const std::string_view& msg, character_encoding enc);

  /**
   * @brief Prints a Message to the log, will append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called.
   * If the encoding is changed during Object Lifetime it will throw!
   *
   * @param msg Message to print.
   */
  void println(const std::string_view& msg);
  void println(const std::u16string_view& msg);
  void println(const std::u32string_view& msg);
  /**
   * @brief Prints a Message to the log, will NOT append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called. Encoding depends on which OS is used: Windows = codepage 1252,
   * Linux = UTF8
   *
   * @param msg Message to print. Style like printf.
   */
  void print(const std::string_view& msg);
  void print(const std::u16string_view& msg);
  void print(const std::u32string_view& msg);
#pragma endregion
#pragma region print wchar

  /**
   * @brief Prints a Message to the log, will append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called. Encoding depends on which OS is used: Windows = UTF16,
   * Linux = UTF16
   *
   * @param msg Message to print.
   */
  void println(const std::wstring_view& msg);
  /**
   * @brief Prints a Message to the log, will NOT append a newline. A new Log
   * message is emitted if a newline character is read or deconstructor is
   * called. Encoding depends on which OS is used: Windows = UTF16,
   * Linux = UTF16
   *
   * @param msg Message to print.
   */
  void print(const std::wstring_view& msg);
#pragma endregion
};
}  // namespace yalog

#endif  // yal_stream_h_INClude
