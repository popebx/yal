#include "pair_sink.h"

pair_sink::pair_sink(std::unique_ptr<yalog::sink> first,
                     yalog::log_level first_level,
                     std::unique_ptr<yalog::sink> second,
                     yalog::log_level second_level) {}

void pair_sink::print(const yalog::log_message &message) {
    for(const auto & sink : this->m_sinks) {
        if(sink.lvl >= message.level) {
            sink.sink->print(message);
        }
    }
}
