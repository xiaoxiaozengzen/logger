find_package(fmt REQUIRED)

add_executable(fmt_example fmt_example.cpp)
target_include_directories(fmt_example
    PRIVATE
    ${fmt_INCLUDE_DIRS}
)
target_link_libraries(fmt_example
    PRIVATE
    ${fmt_LIBRARIES}
)