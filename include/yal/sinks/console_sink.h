#ifndef _console_sink_h_INClude
#define _console_sink_h_INClude
#include <yal/sink.h>

namespace yalog::sinks {
/**
 * @brief Simple Console Error Sink
 *
 */
class console_err : public sink {
public:
  virtual void print(const std::string_view &arg) override;
  virtual void print(const std::wstring_view &arg) override;
  virtual ~console_err() = default;
};
/**
 * @brief Simple Console Out Sink
 *
 */
class console_out : public sink {
public:
  virtual void print(const std::string_view &arg) override;
  virtual void print(const std::wstring_view &arg) override;
  virtual ~console_out() = default;
};
} // namespace yalog::sinks
#endif //_console_sink_h_INClude
