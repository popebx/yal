#include <yal/yal_singleton.hpp>
namespace yalog {
yal_singleton& yal_singleton::operator<<(const std::string_view &arg) {
  this->m_log_instance << arg;
  return yal_singleton::instance();
}

}