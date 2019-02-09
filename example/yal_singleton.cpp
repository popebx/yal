#include <yal/manager.hpp>
#include "sink/console_sink.h"
#include "sink/pair_sink.h"

class singleton {
 public:
  singleton(const singleton&) = delete;
  singleton(singleton&&) = delete;
  singleton& operator=(const singleton&) = delete;
  singleton& operator=(singleton&&) = delete;
  static singleton& instance() {
    static singleton inst{};
    return inst;
  }
  yalog::logger operator()(std::string_view name) { return manager(name); }
  yalog::logger operator()() { return manager(); }
  void flush(std::string_view name) { manager.flush(name); }
  void flush_all() { manager.flush_all(); }

 private:
  singleton() {
    manager.add_new_logger("console",
                           std::make_unique<pair_sink>(std::make_unique<console_out>(), yalog::log_level::DEBUG,
                                                       std::make_unique<console_err>(), yalog::log_level::WARNING),
                           yalog::log_level::DEBUG);
    manager.set_default_logger("console");
  };
  yalog::yal_manager manager;
};

int main() {
  using namespace std::string_view_literals;
  using namespace std::chrono_literals;

  singleton::instance()().debug().println("Debug"sv);
  singleton::instance()().warn() << "Warning\n"sv;
  singleton::instance()().error() << "Error\n"sv;
  singleton::instance()().debug().println("Debug"sv);
  singleton::instance()().warn() << "Warning\n"sv;
  singleton::instance()().error() << "Error\n"sv;
  singleton::instance().flush_all();
  return 0;
}
