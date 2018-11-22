#include <yal/yal_singleton.hpp>

int main() {
  using namespace std::string_view_literals;
  yalog::make_logger("cout", yalog::sinks::console_out{},
                     yalog::log_level::WARNING);
  ylog.set_as_default_logger("cout");
  ylog("cout");
  ylog().warn() << "Hello World\n"sv;
  return 0;
}
