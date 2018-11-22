#ifndef _debug_sink_h_INCLude
#define _debug_sink_h_INCLude

#include <yal/sink.h>

namespace yalog::sinks {
/**
 * @brief Only useable on Windows. Will write every log Message via
 * OutputDebugStream
 *
 */
class debug_sink final : public sink {
public:
  virtual void print(const std::string_view &arg) override;
  virtual void print(const std::wstring_view &arg) override;
  virtual ~debug_sink() = default;
};
} // namespace yalog::sinks
#endif //_debug_sink_h_INCLude
