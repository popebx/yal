#ifndef helper_functions_h_INClude
#define helper_functions_h_INClude
#include <algorithm>
#include <cstdio>
#include <string>
#include <string_view>
#include <vector>
#include <yal/encoding.hpp>
#include <yal/log_level.hpp>

namespace conversion {
template <typename... param>
static std::string format_string(std::string_view str, param &&... parameters) {
  std::string result{};
  int bytes_to_write = std::snprintf(nullptr, 0, str.data(),
                                     std::forward<params...>(parameters...));
  result.resize(bytes_to_write + 1); // Including 0 Terminating character
  bytes_to_write = std::snprintf(result.data(), bytes_to_write + 1, str.data(),
                                 std::forward<params...>(parameters));
  return result;
}

static std::string as_string(std::vector<uint8_t> vec) {
  std::string result;
  result.reserve(vec.size());
  std::transform(vec.begin(), vec.end(), std::back_inserter(result),
                 [](const uint8_t c) { return static_cast<char>(c); });
  return result;
}

static std::u16string as_utf16(std::vector<uint8_t> vec) {
  std::u16string result;
  for (std::size_t i = 0; i < result.size(); i += 2) {
    char16_t out;
    out = vec.at(i) << 8;
    out |= vec.at(i + 1);
    result.push_back(out);
  }
  return result;
}

static std::u32string as_utf32(std::vector<uint8_t> vec) {
  std::u32string result;
  for (std::size_t i = 0; i < vec.size(); i += 4) {
    char32_t out;
    out = vec.at(i) << 24;
    out |= vec.at(i + 1) << 16;
    out |= vec.at(i + 2) << 8;
    out |= vec.at(i + 3);
    result.push_back(out);
  }
  return result;
}

static std::wstring as_wchar(std::vector<uint8_t> data) {
  std::wstring result;
#if defined(_WIN32) || defined(_WIN64)
  auto intermediate = conversion::as_utf16(data);
  result.reserve(intermediate.size());
#else
  throw std::runtime_error("Not implemented!");
#endif
  std::transform(intermediate.begin(), intermediate.end(),
                 std::back_inserter(result),
                 [](auto c) { return static_cast<wchar_t>(c); });
  return result;
}
#pragma region Log Level conversion
static std::string_view as_ascii(yalog::log_level lvl) {
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
static std::string_view as_ansii(yalog::log_level lvl) { return as_ascii(lvl); }
static std::string_view as_utf8(yalog::log_level lvl) { return as_ascii(lvl); }

static std::u16string as_utf16(yalog::log_level lvl) {
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

static std::u32string as_utf32(yalog::log_level lvl) {
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

static std::wstring_view as_wchar(yalog::log_level lvl) {
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
} // namespace conversion
#endif // helper_functions_h_INClude
