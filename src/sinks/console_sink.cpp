#include <iostream>
#include <yal/sinks/console_sink.h>

namespace yalog::sinks {
void console_err::print(const std::string_view &arg) {
  std::cerr << arg.data();
}
void console_err::print(const std::wstring_view &arg) {
  std::wcerr << arg.data();
}

void console_out::print(const std::string_view &arg) {
  std::cout << arg.data();
}
void console_out::print(const std::wstring_view &arg) {
  std::cout << arg.data();
}
} // namespace yalog::sinks