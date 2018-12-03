#include "sink/console_sink.h"
#include <yal/manager.hpp>

int main() {
  using namespace std::string_view_literals;
  using namespace std::chrono_literals;
  yalog::yal_manager manager{};
  manager.add_new_logger("cout", console_out{}, yalog::log_level::WARNING);
  manager.add_new_logger("cerr", console_err{}, yalog::log_level::DEBUG);
  manager.set_default_logger("cout");  
  manager("cout").debug().println("Debug"sv);
  manager("cout").warn() << "Warning\n"sv;
  manager("cout").error() << "Error\n"sv;
  manager("cerr").debug().println("Debug"sv);
  manager("cerr").warn() << "Warning\n"sv;
  manager("cerr").error() << "Error\n"sv;
  manager.flush("cout");
  manager.flush("cerr");
  return 0;
}
