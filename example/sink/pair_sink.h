#ifndef pair_sink_INClude
#define pair_sink_INClude
#include <yal/sink.hpp>

/**
 * @brief Class to combine Sinks to a single Sink (For example Write Debug
 * message to Console and Warnings also to a File)
 * @todo Make it a tuple maybe
 */
class pair_sink : public yalog::sink {
public:
  struct sink_data {
    std::unique_ptr<yalog::sink> sink;
    yalog::log_level lvl;
  };
  template <typename... params> pair_sink(params &&...) {}
  pair_sink(std::unique_ptr<yalog::sink> first, yalog::log_level first_level,
            std::unique_ptr<yalog::sink> second, yalog::log_level second_level);
  virtual void print(const yalog::log_message &message) override;
  virtual ~pair_sink() = default;

private:
  std::vector<sink_data> m_sinks;
};

#endif // pair_sink_INClude
