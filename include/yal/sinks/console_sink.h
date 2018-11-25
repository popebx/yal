#ifndef _console_sink_h_INClude
#define _console_sink_h_INClude
#include <yal/sink.h>
#include <yal/yal_export.h>

namespace yalog::sinks {
/**
 * @brief Simple Console Error Sink
 *
 */
class EXPORT_YAL_API console_err : public sink {
 public:
  virtual void print(const yalog::log_message& msg) override;
  virtual ~console_err() = default;
};
/**
 * @brief Simple Console Out Sink
 *
 */
class EXPORT_YAL_API console_out : public sink {
 public:
  virtual void print(const yalog::log_message& msg) override;
  virtual ~console_out() = default;
};
}  // namespace yalog::sinks
#endif  //_console_sink_h_INClude
