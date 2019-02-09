#include "debug_sink.h"
#include "helper_functions.h"
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <sstream>

void debug_sink::print(const yalog::log_message &message) {
  if (message.encoding == yalog::character_encoding::utf16) {

    std::wstringstream formatted_message;
    formatted_message << L"[" << conversion::as_wchar(message.level) << L"] - "
                      << L"TIME" /*std::put_time(std::localtime(&msg.timestamp),
                   "%Y-%m-%d %X")*/
                      << L" (Thread ID: " << message.thread_id << L") : "
                      << conversion::as_wchar(message.message);
    OutputDebugStringW(formatted_message.str().c_str());
  } else if (message.encoding == yalog::character_encoding::ascii ||
             message.encoding == yalog::character_encoding::ansi) {
    std::stringstream formatted_string{};
    formatted_string << "[" << conversion::as_ascii(message.level) << "] - "
                     << std::put_time(std::localtime(&message.timestamp),
                                      "%Y-%m-%d %X")
                     << " (Thread ID: " << message.thread_id
                     << "): " << conversion::as_string(message.message);
    OutputDebugStringA(formatted_string.str().c_str());
  } else {
    OutputDebugStringA("No String Conversion implemented");
  }
}
