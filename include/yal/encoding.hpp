#ifndef encoding_h_INClude
#define encoding_h_INClude
namespace yalog {
/**
 * @brief Class representing different types of encoding to be able to convert
 * text to different encoding.
 *
 */
enum class character_encoding : int {
  ascii = 7,
  ansi = 8,
  codepage1252 = 8,
  utf8 = 8 * 8,
  utf16 = 16 * 8,
  utf32 = 32 * 8,
};

using char_enc = character_encoding;
}  // namespace yalog
#endif  // encoding_h_INClude
