#include <yal/sinks/console_sink.h>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include "helper_functions.h"

namespace yalog::sinks {

void console_out::print(const yalog::log_message& msg) {
  if (msg.encoding == char_enc::ascii) {
    std::cout << "[" << conversion::to_ascii(msg.level) << "] - " << std::put_time(std::localtime(&msg.timestamp), "%Y-%m-%d %X") << " (Thread ID: " << msg.thread_id
              << "): " << conversion::to_ascii(msg.message, msg.encoding);
  } else {
    std::wcout << L"[" << conversion::to_wchar(msg.level) << L"] - " << L"TIME" /*std::put_time(std::localtime(&msg.timestamp),
                                                                  "%Y-%m-%d %X")*/
               << L" (Thread ID: " << msg.thread_id << L") : " << conversion::to_wchar(msg.message, msg.encoding);
  }
  std::cout << std::flush;
}
void console_err::print(const yalog::log_message& msg) {
  auto time = std::put_time(std::localtime(&msg.timestamp), "%Y-%m-%d %X");
  if (msg.encoding == char_enc::ascii) {
    std::cerr << "[" << conversion::to_ascii(msg.level) << "] - " << time << " (Thread ID: " << msg.thread_id << "): " << conversion::to_utf8(msg.message, msg.encoding);
  } else {
    std::wcerr << L"[" << conversion::to_wchar(msg.level) << L"] - " << L"TIME" << L" (Thread ID: " << msg.thread_id << L") : " << conversion::to_wchar(msg.message, msg.encoding);
  }
  std::cerr << std::flush;
}

}  // namespace yalog::sinks