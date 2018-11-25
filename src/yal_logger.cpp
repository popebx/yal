#include <yal/yal_logger.hpp>

namespace yalog {
logger::logger(log_level arg, sync_sink_queue* ref_sink) : m_log_level{arg}, current_sink{ref_sink} {}

ystream logger::warn() {
  if (this->m_log_level <= log_level::WARNING) {
    return ystream{log_level::WARNING, this->current_sink};
  }
  return this->null_stream;
}

ystream logger::debug() {
  if (this->m_log_level <= log_level::DEBUG) {
    return ystream{log_level::DEBUG, this->current_sink};
  }
  return this->null_stream;
}

ystream logger::error() {
  if (this->m_log_level <= log_level::ERROR) {
    return ystream{log_level::ERROR, this->current_sink};
  }
  return this->null_stream;
}
}  // namespace yalog