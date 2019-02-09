#ifndef debug_sink_INClude
#define debug_sink_INClude
#include <yal/sink.hpp>

class debug_sink : public yalog::sink {
public:
  virtual void print(const yalog::log_message &message) override;
  virtual ~debug_sink() = default;
};
#endif // debug_sink_INClude
