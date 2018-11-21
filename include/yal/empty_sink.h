#ifndef __empty_sink_h_INClude
#define __empty_sink_h_INClude
#include <string_view>
namespace yalog {
class empty_sink {
public:
  void print(const std::string_view &) {}
  void print(const std::wstring_view &) {}
};
} // namespace yalog
#endif //__empty_sink_h_INClude
