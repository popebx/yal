#ifndef _yal_singleton_h_INClude
#define _yal_singleton_h_INClude
#include <type_traits>
#include <yal/yal.hpp>
#include <yal/yal_export.h>

namespace yalog {

class EXPORT_YAL_API yal_singleton {
private:
  yal_singleton() = default;
  ~yal_singleton() = default;
  logger m_log_instance{log_level::DEBUG};

public:
  yal_singleton(const yal_singleton &) = delete;
  yal_singleton(yal_singleton &&) = delete;
  yal_singleton &operator=(const yal_singleton &) = delete;
  yal_singleton &operator=(yal_singleton &&) = delete;
  static yal_singleton &instance() {
    static yal_singleton log_instance;
    return log_instance;
  }
  static yal_singleton &warn() { return yal_singleton::instance(); }
  static yal_singleton &dbg() { return yal_singleton::instance(); }
  static yal_singleton &err() { return yal_singleton::instance(); }
  yal_singleton &operator<<(const std::string_view &arg);
  template <typename value_type,
            typename =
                std::enable_if_t<!std::is_same_v<std::string_view, value_type>>>
  yal_singleton &operator<<(value_type arg) {
    this->m_log_instance << arg;
    return yal_singleton::instance();
  }
};

} // namespace yalog
using yal = yalog::yal_singleton;
#endif //_yal_singleton_h_INClude
