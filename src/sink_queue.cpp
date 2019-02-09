#include <memory>
#include <yal/sink_queue.hpp>

namespace yalog {



sync_sink_queue::sync_sink_queue(std::unique_ptr<yalog::sink>&& sink, yalog::log_level lvl)
    : m_sink{std::move(sink)}, m_level{lvl}, m_consumer{&sync_sink_queue::consume_log_message, this} {}

void sync_sink_queue::consume_log_message() {
  while (this->keep_running) {
    std::unique_lock<std::mutex> lock{this->m_queue_mutex};
    this->m_notify.wait(lock);
    if (!this->m_queue.empty()) {
      this->m_sink->print(this->pop());
    }
  }
}
log_message sync_sink_queue::pop() {
  auto result = this->m_queue.top();
  this->m_queue.pop();
  return result;
}

void sync_sink_queue::push(log_message&& new_msg) {
  std::unique_lock<std::mutex> lock{this->m_queue_mutex};
  this->m_queue.push(std::move(new_msg));
  this->m_notify.notify_one();
}

void sync_sink_queue::flush() {
  std::unique_lock<std::mutex> lock{this->m_queue_mutex};
  while (!this->m_queue.empty()) {
    auto msg = this->m_queue.top();
    this->m_sink->print(msg);
    this->m_queue.pop();
  }
}

sync_sink_queue::~sync_sink_queue() noexcept {
  while (this->m_queue.size() > 0) {
    this->m_notify.notify_all();
  }
  this->keep_running = false;
  this->m_notify.notify_one();
  if (this->m_consumer.joinable()) {
    this->m_consumer.join();
  }
}
}  // namespace yalog