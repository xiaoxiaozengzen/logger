#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include "fmt/args.h"
#if 0
#include "fmt/chrono.h"
#endif

struct Point {
  int x;
  int y;
};

template<>
struct fmt::formatter<Point> {
  auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin()) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const Point& p, FormatContext& ctx) -> decltype(ctx.out()) {
    return fmt::format_to(ctx.out(), "Point({}, {})", p.x, p.y);
  }
};

void args_test() {
  fmt::dynamic_format_arg_store<fmt::format_context> store;

  // basic types
  store.push_back(42);
  store.push_back("Hello");
  store.push_back(3.14);
  std::string str = fmt::vformat("Number: {}, String: {}, Float: {}", store);
  std::cout << str << std::endl;

  // string ref
  store.clear();
  char str1[] = "1234567890";
  store.push_back(str1);
  store.push_back(std::cref(str1));
  store.push_back(fmt::string_view{str1});
  str1[0] = 'a';
  std::string str3 = fmt::vformat("String: {}, String ref: {}, String view: {}", store);
  std::cout << str3 << std::endl;

  // custom types
  store.clear();
  Point p1{1, 2};
  store.push_back(p1);
  std::string str4 = fmt::vformat("{}", store);
  std::cout << str4 << std::endl;

}

#if 0
void chrono_test() {
  auto tm = std::tm();
  tm.tm_year = 116;
  tm.tm_mon = 3;
  tm.tm_mday = 25;
  tm.tm_hour = 11;
  tm.tm_min = 22;
  tm.tm_sec = 33;

  auto str = fmt::format("The date is {:%Y-%m-%d %H:%M:%S}.", tm);
  std::cout << str << std::endl;
}
#endif

int main() {
    std::cout << "===================== args_test =====================" << std::endl;
    args_test();
#if 0
    std::cout << "===================== chrono_test =====================" << std::endl;
    chrono_test();
#endif
    return 0;
}