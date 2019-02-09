#ifndef pair_sink_INClude
#define pair_sink_INClude
#include <yal/sink.hpp>

/**
 * @brief Class to combine Sinks to a single Sink (For example Write Debug
 * message to Console and Warnings also to a File)
 * @todo Make it a tuple maybe
 */
class pair_sink : public yalog::sink {
  pair_sink(std::unique_ptr<yalog::sink> one, std::unique_ptr<yalog::sink> two);
  virtual void print(const yalog::log_message &message) override;
  virtual ~pair_sink() = default;

private:
  std::unique_ptr<yalog::sink> m_first;
  std::unique_ptr<yalog::sink> m_second;
};

#endif // pair_sink_INClude