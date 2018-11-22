#include <Windows.h>
#include <yal/sinks/debug_sink.h>

namespace yalog::sinks {
void debug_sink::print(const std::string_view &arg) {
  OutputDebugStringA(arg.data());
}
void debug_sink::print(const std::wstring_view &arg) {
  OutputDebugStringW(arg.data());
}
} // namespace yalog::sinks