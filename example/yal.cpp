#include "sink/debug_sink.h"
#include "sink/file_sink.h"
#include <yal/manager.hpp>

int main() {
  yalog::yal_manager manager{};
  manager.add_new_logger("debug", debug_sink{}, yalog::log_level::DEBUG);
  manager.add_new_logger(
      "file", file_sink{std::filesystem::path{"log"}, yalog::char_enc::utf8},
      yalog::log_level::WARNING);
  manager.set_default_logger("file");
  manager("debug").debug() << u"Hello World";
  manager().warn() << u8"Hi";
  return 0;
}