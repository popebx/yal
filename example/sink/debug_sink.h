#ifndef debug_sink_INClude
#define debug_sink_INClude
#include <yal/sink.hpp>
/**
 * @brief Sink which prints to OutputDebugString / System.Diagnostics.Debug
 *
 */
class debug_sink : public yalog::sink {
public:
  virtual void print(const yalog::log_message &message) override;
  virtual ~debug_sink() = default;
};
#endif // debug_sink_INClude
