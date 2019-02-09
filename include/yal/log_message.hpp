#ifndef log_message_h_INClude
#define log_message_h_INClude
#include <cstdint>
#include <ctime>
#include <thread>
#include <vector>
#include <yal/encoding.hpp>
#include <yal/log_level.hpp>

namespace yalog {

struct log_message {
  std::time_t timestamp{0};
  std::vector<uint8_t> message;
  yalog::char_enc encoding{yalog::char_enc::ascii};
  log_level level{yalog::log_level::DEBUG};
  std::thread::id thread_id;
  bool operator==(const log_message& rhs) const { return this->timestamp == rhs.timestamp; }
  bool operator>(const log_message& rhs) const { return this->timestamp > rhs.timestamp; };
};
}  // namespace yalog
#endif  // log_message_h_INClude
