#ifndef __empty_sink_h_INClude
#define __empty_sink_h_INClude
#include <string_view>
#include <yal/sink.h>
namespace yalog::sinks {

/**
 * @brief Empty Sink is getting used to hide some messages.
 *
 */
class empty_sink final : public sink {
public:
  virtual void print(const std::string_view &) override {}
  virtual void print(const std::wstring_view &) override {}
  virtual ~empty_sink() = default;
};
} // namespace yalog::sinks
#endif //__empty_sink_h_INClude
