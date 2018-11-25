#ifndef log_message_h_INClude
#define log_message_h_INClude
#include <yal/encoding.h>
#include <yal/log_level.h>
#include <cstdint>
#include <ctime>
#include <thread>
#include <vector>

namespace yalog {

struct log_message {
  std::time_t timestamp;
  std::vector<uint8_t> message;
  yalog::char_enc encoding;
  log_level level;
  std::thread::id thread_id;
  bool operator==(const log_message& rhs) const { return this->timestamp == rhs.timestamp; }
  bool operator>(const log_message& rhs) const { return this->timestamp > rhs.timestamp; };
};
}  // namespace yalog
#endif  // log_message_h_INClude
