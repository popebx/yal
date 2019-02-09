#ifndef _yal_singleton_h_INClude
#define _yal_singleton_h_INClude
#include <yal/dll_export.h>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <yal/logger.hpp>

namespace yalog {

/**
 * @brief Singleton Logger Manager. It will hold all logger created during the
 * lifetime of the application.
 *
 */
class EXPORT_YAL_API yal_manager {
 private:
  std::unordered_map<std::string, std::unique_ptr<yalog::sync_sink_queue>> m_logger;
  yalog::sync_sink_queue* m_standard_sink = nullptr;

  sync_sink_queue* find(std::string_view name) const;

 public:
  yal_manager() = default;
  ~yal_manager() = default;

  yal_manager(const yal_manager&) = delete;
  yal_manager(yal_manager&&) = delete;
  yal_manager& operator=(const yal_manager&) = delete;
  yal_manager& operator=(yal_manager&&) = delete;
  /**
   * @brief Looks up a logger and returns it otherwise it will throw a
   * std::runtime_error
   *
   *
   * @param name Name of the Logger
   * @return logger& Instance of the logger
   */
  logger operator()(std::string_view name) const;
  /**
   * @brief Returns a standard logger if is set otherwise will throw a
   * std::runtime_error
   *
   *
   * @return logger& Instance of the standard logger
   */
  logger operator()() const;

  /**
   * @brief Set the default logger by name. It will throw an std::runtime_error
   * if the name isn't found
   *
   * @param name Name of the logger
   */
  void set_default_logger(std::string_view name);
  void flush(std::string_view name);
  void flush();
  void flush_all();
  logger add_new_logger(const std::string_view& name, std::unique_ptr<sink>&& new_sink, const log_level level);
};

}  // namespace yalog

#endif  //_yal_singleton_h_INClude
