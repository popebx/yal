#ifndef _console_sink_h_INClude
#define _console_sink_h_INClude
#include <iostream>
#include <yal/sink.h>

namespace yalog {

class console_err {
  void print(const std::string_view &arg) { std::cerr << arg.data(); }
  void print(const std::wstring_view &arg) { std::wcerr << arg.data(); }
};
class console_out {
  void print(const std::string_view &arg) { std::cout << arg.data(); }
  void print(const std::wstring_view &arg) { std::cout << arg.data(); }
};
} // namespace yalog
#endif //_console_sink_h_INClude
