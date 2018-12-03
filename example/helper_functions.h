#ifndef helper_functions_h_INClude
#define helper_functions_h_INClude
#include <yal/encoding.h>
#include <yal/log_level.h>
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace conversions {
namespace {
template <yalog::char_enc to>
auto convert(const std::vector<uint8_t>& from) {
  if constexpr (to == yalog::char_enc::ascii || to == yalog::char_enc::ansi || to == yalog::char_enc::utf8) {
    std::string result;
    result.reserve(from.size());
    std::transform(from.begin(), from.end(), std::back_inserter(result), [](uint8_t c) { return static_cast<char>(c); });
    return result;
  } else if constexpr (to == yalog::char_enc::utf16) {
    std::u16string result;
    if (!(from.size() % 2 == 0)) {
      throw std::runtime_error("UTF16 Message consist of weird number bytes");
    }
    result.reserve(from.size() / 2);
    for (std::size_t i = 0; i < from.size(); i += 2) {
      char16_t out;
      out = from[i] << 8;
      out |= from[i + 1];
      result.push_back(out);
    }
    result.reserve(from.size() / 2);
    return u"";
  } else if constexpr (to == yalog::char_enc::utf32) {
    std::u32string result;
    if (!(from.size() % 4 == 0)) {
      throw std::runtime_error("UTF32 Message consist of weird number bytes");
    }
    result.reserve(from.size() / 4);
    for (std::size_t i = 0; i < from.size(); i += 4) {
      char32_t out;
      out = from[i] << 24;
      out |= from[i + 1] << 16;
      out |= from[i + 2] << 8;
      out |= from[i + 3];
      result.push_back(out);
    }
    return result;
  } else {
    throw std::runtime_error("Unreachable");
  }
}
}  // namespace
std::string to_ascii(const std::vector<uint8_t>& message, yalog::char_enc encoding);
std::string to_ansii(const std::vector<uint8_t>& message, yalog::char_enc encoding);
std::string to_utf8(const std::vector<uint8_t>& message, yalog::char_enc encoding);
std::u16string to_utf16(const std::vector<uint8_t>& message, yalog::char_enc encoding);
std::u32string to_utf32(const std::vector<uint8_t>& message, yalog::char_enc encoding);

/// ASCII & ANSII and UTF-8 are all the same as long as its representable in ascii
std::string_view to_ascii(yalog::log_level lvl); /* {
  switch (lvl) {
    case yalog::log_level::DEBUG:
      return "DEBUG";
    case yalog::log_level::WARNING:
      return "WARNING";
    case yalog::log_level::ERROR:
      return "ERROR";
  }
  return "";
}*/

std::u16string to_utf16(yalog::log_level lvl); /* {
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
 }*/

std::u32string to_utf32(yalog::log_level lvl); /* {
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
 }*/

}  // namespace conversions

#endif  // helper_functions_h_INClude
