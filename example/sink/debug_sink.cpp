#include "debug_sink.h"
#include "helper_functions.h"
#include <Windows.h>
void debug_sink::print(const yalog::log_message &message) {
  if (message.encoding == yalog::character_encoding::utf16) {
    std::wstring str = conversion::as_wchar(message.message);
    OutputDebugStringW(str.c_str());
  } else if (message.encoding == yalog::character_encoding::ascii ||
             message.encoding == yalog::character_encoding::ansi) {
    std::string str = conversion::as_string(message.message);
    OutputDebugStringA(str.c_str());
  } else {
    OutputDebugStringA("No String Conversion implemented");
  }
}
