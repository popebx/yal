#include "pair_sink.h"

pair_sink::pair_sink(std::unique_ptr<yalog::sink> && first,
                     yalog::log_level first_level,
                     std::unique_ptr<yalog::sink> &&second,
                     yalog::log_level second_level) {

  this->m_sinks.emplace_back(std::move(first), first_level);
  this->m_sinks.emplace_back(std::move(second), second_level);
}

void pair_sink::print(const yalog::log_message &message) {
  for (const auto &sink : this->m_sinks) {
    if (sink.second >= message.level) {
      sink.first->print(message);
    }
  }
}
