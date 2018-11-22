#ifndef _yal_singleton_h_INClude
#define _yal_singleton_h_INClude
#include <string>
#include <type_traits>
#include <unordered_map>
#include <yal/yal.hpp>
#include <yal/yal_export.h>

namespace yalog {

/**
 * @brief Creates a new Logger with an log level and a sink
 *
 * @param name Name of the logger, which has to be unique otherwise this method
 * will throw!
 * @param new_sink New sink which will be owned by this logger
 * @param level Log Level which this logger should take
 * @return yalog::logger& Logger Object which can be used directly for logging.
 * You can get the reference from yal_manager.
 */
yalog::logger &make_logger(const std::string_view &name, sink &&new_sink,
                           const log_level level);

/**
 * @brief Singleton Logger Manager. It will hold all logger created during the
 * lifetime of the application.
 *
 */
class EXPORT_YAL_API yal_manager {
  friend yalog::logger &make_logger(const std::string_view &, sink &&,
                                    const log_level);

private:
  yal_manager() = default;
  ~yal_manager() = default;
  std::unordered_map<std::string, yalog::logger> m_logger;
  yalog::logger *standard_logger;
  logger &add_new_logger(const std::string_view &name, sink &&new_sink,
                         const log_level level);

public:
#pragma region Singleton
  yal_manager(const yal_manager &) = delete;
  yal_manager(yal_manager &&) = delete;
  yal_manager &operator=(const yal_manager &) = delete;
  yal_manager &operator=(yal_manager &&) = delete;
  /**
   * @brief Returns a Instance to the Manager.
   *
   * @return yal_manager& Only Instance of the manager
   */
  static yal_manager &instance() {
    static yal_manager log_instance;
    return log_instance;
  }
#pragma endregion
  /**
   * @brief Looks up a logger and returns it otherwise it will throw a
   * std::runtime_error
   *
   * @todo Subscript Operator?
   * @todo const? Threading?
   *
   * @param name Name of the Logger
   * @return logger& Instance of the logger
   */
  logger &operator()(std::string_view name) {
    // TODO: Move to cpp
    auto result = std::find_if(
        this->m_logger.begin(), this->m_logger.end(),
        [&name](const auto &entry) { return name == entry.first; });
    if (result == this->m_logger.end()) {
      throw std::runtime_error("Logger not found");
    }
    return result->second;
  }
  /**
   * @brief Returns a standard logger if is set otherwise will throw a
   * std::runtime_error
   *
   * @todo if i move (std::string_view) to subscript what happends here? std()?
   *
   * @return logger& Instance of the standard logger
   */
  logger &operator()() {
    // TODO: move to cpp
    if (this->standard_logger != nullptr) {
      return *this->standard_logger;
    }
    // TODO: Set standard logger to nullptr?
    throw std::runtime_error("Logger not found");
  }

  /**
   * @brief Set the default logger by name. It will throw an std::runtime_error
   * if the name isn't found
   *
   * @param name Name of the logger
   */
  void set_default_logger(std::string_view name) {
    // TODO: Move to cpp
    this->standard_logger = &this->operator()(name);
  }
};

} // namespace yalog
auto &ylog = yalog::yal_manager::instance();
#endif //_yal_singleton_h_INClude
