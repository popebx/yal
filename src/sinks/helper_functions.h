#ifndef helper_functions_h_INClude
#define helper_functions_h_INClude
#include <yal/log_level.h>
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

std::string to_ansii(const std::vector<uint8_t>& msg) {
  std::string result;
  result.reserve(msg.size());
  std::transform(msg.begin(), msg.end(), std::back_inserter(result), [](uint8_t c) { return static_cast<char>(c); });
  return result;
}

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

std::u16string to_u16(yalog::log_level lvl) {
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

std::u32string to_u32(yalog::log_level lvl) {
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

#endif  // helper_functions_h_INClude
