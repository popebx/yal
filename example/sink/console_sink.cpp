#include "console_sink.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include "helper_functions.h"

void console_out::print(const yalog::log_message& msg) {
  if (msg.encoding == yalog::char_enc::ascii) {
    std::cout << "[" << conversion::to_ascii(msg.level) << "] - " << std::put_time(std::localtime(&msg.timestamp), "%Y-%m-%d %X")
              << " (Thread ID: " << msg.thread_id << "): " << conversion::as_string(msg.message);
  } else if (msg.encoding == yalog::char_enc::utf16) {
    std::wcout << L"[" << conversion::to_wchar(msg.level) << L"] - " << L"TIME" /*std::put_time(std::localtime(&msg.timestamp),
                                                                  "%Y-%m-%d %X")*/
               << L" (Thread ID: " << msg.thread_id << L") : " << conversion::as_wchar(msg.message);
  }
  std::cout << std::flush;
}
void console_err::print(const yalog::log_message& msg) {
  auto time = std::put_time(std::localtime(&msg.timestamp), "%Y-%m-%d %X");
  if (msg.encoding == yalog::char_enc::ascii) {
    std::cerr << "[" << conversion::to_ascii(msg.level) << "] - " << time << " (Thread ID: " << msg.thread_id
              << "): " << conversion::as_string(msg.message).c_str();
  } else {
    std::wcerr << L"[" << conversion::to_wchar(msg.level) << L"] - " << L"TIME" << L" (Thread ID: " << msg.thread_id << L") : "
               << conversion::as_wchar(msg.message);
  }
  std::cerr << std::flush;
}
