#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h" // support for loading levels from the environment variable
#include "spdlog/cfg/argv.h" // support for loading levels from command line arguments
#include "spdlog/sinks/basic_file_sink.h" // support for basic file sink
#include "spdlog/sinks/stdout_color_sinks.h" // support for colored console output
#include "spdlog/logger.h" // support for logger

/**
 * 日志级别：(默认是 info)
 * - trace: 详细的调试信息，0
 * - debug: 调试信息，1
 * - info: 一般信息，2
 * - warn: 警告信息，3
 * - err: 错误信息，4
 * - critical: 严重错误信息，5
 * - off: 关闭日志，6
 */
void set_log_level(int argc, char* argv[]) {
  /**
   * inline void load_env_levels(const char* var = "SPDLOG_LEVEL")
   * @brief 默认情况下读取环境变量 SPDLOG_LEVEL 的值来设置日志级别
   * 
   * SPDLOG_LEVEL=info,mylogger=trace ：设置日志级别为 info，并将 mylogger 的日志级别为 trace
   */
  spdlog::cfg::load_env_levels();

  spdlog::trace("This is a trace message");
  spdlog::debug("This is a debug message");
  spdlog::info("This is an info message");
  spdlog::warn("This is a warn message");
  spdlog::error("This is an error message");
  spdlog::critical("This is a critical message");

  // Set log level from command line arguments
  // 有先后顺序，后者会覆盖前者设置的日志级别
  spdlog::cfg::load_argv_levels(argc, argv);
  spdlog::trace("This is a trace message from command line");
  spdlog::debug("This is a debug message from command line");
  spdlog::info("This is an info message from command line");
  spdlog::warn("This is a warn message from command line");
  spdlog::error("This is an error message from command line");
  spdlog::critical("This is a critical message from command line");

  // set log level when running the program
  spdlog::set_level(spdlog::level::critical); // Set global log level to trace
  spdlog::info("This is an info message after setting log level to critical");
  spdlog::set_level(spdlog::level::info); // Set global log level to info
  spdlog::info("This is an info message after setting log level to info");
}

void set_pattern() {
  spdlog::info("This is an info message with default pattern");

  /**
   * void set_pattern(std::string pattern, pattern_time_type time_type = pattern_time_type::local);
   * 
   * @brief 设置日志输出格式
   * @param pattern 日志输出格式
   * @param time_type 日志时间类型，默认是 local
   * 
   * enum pattern_time_type {
   *   local, // 本地时间
   *   utc // UTC 时间
   * };
   * 
   * 所有的格式化参数可以参考pattern_formatter-inl.h
   */
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%F %a] [%^%l%$] [date %c] [pid %P] [thread %t] %v");
  spdlog::info("This is an info message with custom pattern");
  spdlog::set_pattern("%+"); // 设置为默认格式
  spdlog::info("This is an info message with default pattern");
}

void logger_example() {
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::warn);
  console_sink->set_pattern("[console_sink] [%n] [%^%l%$] %v");

  // 会覆盖文件旧有的内容
  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multi_sink_example.log", true);
  file_sink->set_level(spdlog::level::trace);
  file_sink->set_pattern("[file_sink] [%n] [%^%l%$] %v");

  std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>("logger_example", spdlog::sinks_init_list{console_sink, file_sink});
  logger->set_level(spdlog::level::debug); // Set global log level to trace
  logger->trace("This is a trace message from logger");
  logger->debug("This is a debug message from logger");
  logger->info("This is an info message from logger");
  logger->warn("This is a warn message from logger");
  logger->error("This is an error message from logger");
  logger->critical("This is a critical message from logger");

  // set the default logger to the logger created above
  spdlog::set_default_logger(logger);
}

void global_fun_example() {
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::warn);
  console_sink->set_pattern("[anthoer_console_sink] [%n] [%^%l%$] %v");

  std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>("test_logger", console_sink);
  logger->set_level(spdlog::level::debug); // Set global log level to trace
  logger->trace("This is a trace message from test");
  logger->debug("This is a debug message from test");
  logger->info("This is an info message from test");
  logger->warn("This is a warn message from test");
  logger->error("This is an error message from test");
  logger->critical("This is a critical message from test");

  // create and register a logger
  auto created_logger = spdlog::create<spdlog::sinks::stdout_color_sink_mt>("created_logger");
  created_logger->set_level(spdlog::level::debug); // Set global log level to trace
  spdlog::get("created_logger")->trace("This is a trace message from created_logger");
  spdlog::get("created_logger")->debug("This is a debug message from created_logger");
  spdlog::get("created_logger")->info("This is an info message from created_logger");
  spdlog::get("created_logger")->warn("This is a warn message from created_logger");
  spdlog::get("created_logger")->error("This is an error message from created_logger");
  spdlog::get("created_logger")->critical("This is a critical message from created_logger");

  // initialize and register a logger
  spdlog::initialize_logger(logger);
  logger->trace("This is a trace message from test after initialize_logger");
  logger->debug("This is a debug message from test after initialize_logger");
  logger->info("This is an info message from test after initialize_logger");
  logger->warn("This is a warn message from test after initialize_logger");
  logger->error("This is an error message from test after initialize_logger");
  logger->critical("This is a critical message from test after initialize_logger");

  // get
  spdlog::get("test_logger")->trace("This is a trace message from test after get");
  spdlog::get("test_logger")->debug("This is a debug message from test after get");
  spdlog::get("test_logger")->info("This is an info message from test after get");
  spdlog::get("test_logger")->warn("This is a warn message from test after get");
  spdlog::get("test_logger")->error("This is an error message from test after get");
  spdlog::get("test_logger")->critical("This is a critical message from test after get");
  spdlog::get("logger_example")->trace("This is a trace message from test after get logger_example");
  spdlog::get("logger_example")->debug("This is a debug message from test after get logger_example");
  spdlog::get("logger_example")->info("This is an info message from test after get logger_example");
  spdlog::get("logger_example")->warn("This is a warn message from test after get logger_example");
  spdlog::get("logger_example")->error("This is an error message from test after get logger_example");
  spdlog::get("logger_example")->critical("This is a critical message from test after get logger_example");
}

void all() {
  spdlog::trace("This is a trace message from all");
  spdlog::debug("This is a debug message from all");
  spdlog::info("This is an info message from all");
  spdlog::warn("This is a warn message from all");
  spdlog::error("This is an error message from all");
  spdlog::critical("This is a critical message from all");
}

int main(int argc, char* argv[]) {
  std::cout << "======================= set_log_level =======================" << std::endl;
  set_log_level(argc, argv);
  std::cout << "======================= set_pattern =======================" << std::endl;
  set_pattern();
  std::cout << "======================= logger_example =======================" << std::endl;
  logger_example();
  std::cout << "======================= global_fun_example =======================" << std::endl;
  global_fun_example();
  std::cout << "======================= all =======================" << std::endl;
  all();

  return 0;
}