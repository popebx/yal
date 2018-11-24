#ifndef safe_queue_h_INClude
#define safe_queue_h_INClude
#include <mutex>
#include <queue>
#include <thread>
#include <yal/sink.h>

namespace yalog {



/**
 * @brief Simple Thread safe Queue implementation for communication between
 * stream and sink (Multi Producer,single consumer)
 *
 * @todo maybe sorted list?
 *
 */
class sync_sink_queue {

  sync_sink_queue(yalog::sink &sink) : m_sink{sink} {}
  void push(uint64_t timestamp, std::string_view message, std::thread::id);

private:
  /**
   * @brief A Log Message, with its message encoded in UTF-8
   *
   */
  struct log_message {
    uint64_t timestamp;
    std::string message;
    std::thread::id thread_id;
    bool operator==(const log_message &) const;
    bool operator==(log_message &&) const;
    bool operator<(const log_message &) const;
    bool operator<(log_message &&) const;
  };
  /**
   * @brief Consumer writing everything out of the queue into the sink
   *
   */
  std::thread m_consumer;
  std::mutex m_queue_mutex;
  yalog::sink &m_sink;

  std::priority_queue<log_message> m_queue;
};


class sink_queue {

}
} // namespace yalog
#endif // safe_queue_h_INClude
