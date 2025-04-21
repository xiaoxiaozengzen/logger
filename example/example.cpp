#include <iostream>

#include "log_manager.hpp"

int main() {
  LogManager::getInstance("default_logger");

  MY_LOG_TRACE("This is a trace message");
  MY_LOG_DEBUG("This is a debug message {}", 10);
  MY_LOG_INFO("This is an info message {}", "INFO");
  MY_LOG_WARN("This is a warning message {}", 3.14);
  MY_LOG_ERROR("This is an error message {}", 'a');
  MY_LOG_CRITICAL("This is a critical message {}", "CRITICAL");

  return 0;
}