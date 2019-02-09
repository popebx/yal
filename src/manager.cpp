#include <yal/manager.hpp>
namespace yalog {

logger yal_manager::operator()(std::string_view name) const {
  auto* sink = this->find(name);
  return logger{sink->level(), sink};
}

sync_sink_queue* yal_manager::find(std::string_view name) const {
  auto result = std::find_if(this->m_logger.begin(), this->m_logger.end(),
                             [&name](const auto& entry) { return name == entry.first; });
  if (result == this->m_logger.end()) {
    throw std::runtime_error("Logger not found");
  }
  return result->second.get();
}

void yal_manager::flush_all() {
  for (auto& [key, value] : this->m_logger) {
    value->flush();
  }
}

void yal_manager::flush() {
  if (this->m_standard_sink != nullptr) {
    this->m_standard_sink->flush();
    return;
  }
  throw std::logic_error("No default Logger set");
}

void yal_manager::flush(std::string_view name) {
  auto* sink = this->find(name);
  sink->flush();
}

logger yal_manager::operator()() const {
  if (this->m_standard_sink != nullptr) {
    return logger{this->m_standard_sink->level(), this->m_standard_sink};
  }
  throw std::logic_error("Logger not found");
}
void yal_manager::set_default_logger(std::string_view name) {
  this->m_standard_sink = this->find(name);
}

logger yal_manager::add_new_logger(const std::string_view& name, std::unique_ptr<sink>&& new_sink, const log_level level) {
  this->m_logger.emplace(name, std::make_unique<yalog::sync_sink_queue>(std::forward<std::unique_ptr<sink>&&>(new_sink), level));
  return this->operator()(name);
}
}  // namespace yalog