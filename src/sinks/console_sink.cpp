#include <yal/sinks/console_sink.h>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include "helper_functions.h"
namespace yalog::sinks {

void console_out::print(const yalog::log_message& msg) {
  if (msg.encoding == char_enc::codepage1252 || msg.encoding == char_enc::ascii) {
    std::cout << "[" << to_ascii(msg.level) << "] - " << std::put_time(std::localtime(&msg.timestamp), "%Y-%m-%d %X")
              << " (Thread ID: " << msg.thread_id << "): " << to_ansii(msg.message);
  } else if (msg.encoding == char_enc::utf16) {
    std::wcout << L"[" << "MessageLevel" << L"] - " << L"TIME" /*std::put_time(std::localtime(&msg.timestamp), "%Y-%m-%d %X")*/
               << L" (Thread ID: " << msg.thread_id << L") : ";
  }
  std::cout << std::flush;
}
void console_err::print(const yalog::log_message& msg) {
  if (msg.encoding == char_enc::codepage1252 || msg.encoding == char_enc::ascii) {
    std::cerr << "[" << to_ascii(msg.level) << "] - " << std::put_time(std::localtime(&msg.timestamp), "%Y-%m-%d %X")
              << " (Thread ID: " << msg.thread_id << "): " << to_ansii(msg.message);
  }
  std::cerr << std::flush;
}
}  // namespace yalog::sinks