#ifndef safe_queue_h_INClude
#define safe_queue_h_INClude
#include <yal/log_level.hpp>
#include <yal/sink.hpp>
#include <atomic>
#include <mutex>
#include <queue>
#include <thread>
#include <yal/log_message.hpp>

namespace yalog {

/**
 * @brief Simple Thread safe Queue implementation for communication between
 * stream and sink (Multi Producer,single consumer)
 *
 * @todo maybe sorted list?
 *
 */
class sync_sink_queue {
 public:
  sync_sink_queue(yalog::sink&& sink, yalog::log_level lvl);
  ~sync_sink_queue() noexcept;
  void push(log_message&& new_msg);

  log_level level() const { return this->m_level; }
  void flush();
 private:
  void consume_log_message();
  log_message pop();

  std::atomic_bool keep_running = true;
  std::condition_variable m_notify;
  std::mutex m_queue_mutex{};
  yalog::sink& m_sink;
  const yalog::log_level m_level;
  std::priority_queue<log_message, std::vector<log_message>, std::greater<log_message>> m_queue{};
  std::thread m_consumer;
};
}  // namespace yalog
#endif  // safe_queue_h_INClude
