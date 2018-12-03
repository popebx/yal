#ifndef _console_sink_h_INClude
#define _console_sink_h_INClude
#include <yal/sink.hpp>
#include <yal/dll_export.h>

/**
 * @brief Simple Console Error Sink
 *
 */
class console_err : public yalog::sink {
 public:
  virtual void print(const yalog::log_message& msg) override;
  virtual ~console_err() = default;
};
/**
 * @brief Simple Console Out Sink
 *
 */
class console_out : public yalog::sink {
 public:
  virtual void print(const yalog::log_message& msg) override;
  virtual ~console_out() = default;
};
#endif  //_console_sink_h_INClude
