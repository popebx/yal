#ifndef helper_functions_h_INClude
#define helper_functions_h_INClude
#include <yal/encoding.h>
#include <yal/log_level.h>
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace conversion {

std::string as_string(std::vector<uint8_t> vec) {}

std::u16string as_utf16(std::vector<uint8_t> vec) {}

std::u32string as_utf32(std::vector<uint8_t> vec) {}

std::wstring to_wchar(std::vector<uint8_t> data, yalog::char_enc encoding) {
  std::wstring result;
#if defined(_WIN32) || defined(_WIN64)
  auto intermediate = to_utf16(data, encoding);
  result.reserve(intermediate.size());
#else
#endif
  std::transform(intermediate.begin(), intermediate.end(), std::back_inserter(result), [](auto c) { return static_cast<wchar_t>(c); });
  return result;
}
#pragma region Log Level conversion
std::string_view to_ascii(yalog::log_level lvl) {
  switch (lvl) {
    case yalog::log_level::DEBUG:
      return "DEBUG";
    case yalog::log_level::WARNING:
      return "WARNING";
    case yalog::log_level::ERROR:
      return "ERROR";
  }
  return "";
}
std::string_view to_ansii(yalog::log_level lvl) {
  return to_ascii(lvl);
}
std::string_view to_utf8(yalog::log_level lvl) {
  return to_ascii(lvl);
}

std::u16string to_utf16(yalog::log_level lvl) {
  using namespace std::string_literals;
  switch (lvl) {
    case yalog::log_level::DEBUG:
      return u"DEBUG";
    case yalog::log_level::WARNING:
      return u"WARNING";
    case yalog::log_level::ERROR:
      return u"ERROR";
  }
  return u"";
}

std::u32string to_utf32(yalog::log_level lvl) {
  using namespace std::string_literals;
  switch (lvl) {
    case yalog::log_level::DEBUG:
      return U"DEBUG";
    case yalog::log_level::WARNING:
      return U"WARNING";
    case yalog::log_level::ERROR:
      return U"ERROR";
  }
  return U"";
}

std::wstring_view to_wchar(yalog::log_level lvl) {
  switch (lvl) {
    case yalog::log_level::DEBUG:
      return L"DEBUG";
    case yalog::log_level::WARNING:
      return L"WARNING";
    case yalog::log_level::ERROR:
      return L"ERROR";
  }
  return L"";
}

#pragma endregion
}  // namespace conversion
#endif  // helper_functions_h_INClude
