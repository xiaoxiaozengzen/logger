#include <iostream>

#include "log_manager.hpp"

int main() {
  LogManager::getInstance("default_logger");

  MY_LOG_TRACE("This is a trace message");
  MY_LOG_DEBUG("This is a debug message {}", 10);

  return 0;
}