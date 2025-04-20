find_package(spdlog REQUIRED)

add_executable(spdlog_example spdlog_example.cpp)
target_include_directories(spdlog_example PRIVATE ${spdlog_INCLUDE_DIRS})
target_link_libraries(spdlog_example PRIVATE ${spdlog_LIBRARIES})