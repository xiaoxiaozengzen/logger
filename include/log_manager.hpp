#ifndef LOG_MANAGER_HPP_
#define LOG_MANAGER_HPP_

#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class LogManager {
public:
  static LogManager& getInstance(std::string logger_name = "default_logger") {
    static LogManager instance("default_logger");
    return instance;
  }

  void Init(std::string logger_name) {
    default_spd_logger_.set_pattern("[%Y-%m-%d %H:%M:%S.%F] [%n] [%t] [%^%l%$] %v");
    default_spd_logger_.set_level(spdlog::level::trace);
    spdlog::set_default_logger(std::make_shared<spdlog::logger>(default_spd_logger_));
  }

  spdlog::logger& getLogger() {
    return default_spd_logger_;
  }

private:
  LogManager(std::string logger_name):default_spd_logger_{logger_name, std::make_shared<spdlog::sinks::stdout_color_sink_mt>()} 
  {
    Init(logger_name);
  }

  ~LogManager() {} // Destructor

  // Delete copy constructor and assignment operator
  LogManager(const LogManager&) = delete;
  LogManager& operator=(const LogManager&) = delete;
  LogManager(LogManager&&) = delete;
  LogManager& operator=(LogManager&&) = delete;

  spdlog::logger default_spd_logger_;
};

#define MY_LOG_TRACE(...) \
  LogManager::getInstance().getLogger().trace(__VA_ARGS__)
#define MY_LOG_DEBUG(...) \
  LogManager::getInstance().getLogger().debug(__VA_ARGS__)
#define MY_LOG_INFO(...) \
  LogManager::getInstance().getLogger().info(__VA_ARGS__)
#define MY_LOG_WARN(...) \
  LogManager::getInstance().getLogger().warn(__VA_ARGS__)
#define MY_LOG_ERROR(...) \
  LogManager::getInstance().getLogger().error(__VA_ARGS__)
#define MY_LOG_CRITICAL(...) \
  LogManager::getInstance().getLogger().critical(__VA_ARGS__)


#endif // LOG_MANAGER_HPP_