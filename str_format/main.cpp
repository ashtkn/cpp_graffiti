#include <cstdarg>

#include <iostream>
#include <string>

/**
 * @brief 1023文字（+ヌル文字）までの文字列をフォーマットして返す
 */
std::string StrFormat(const char* format, ...) {
  va_list args;
  va_start(args, format);
  char buffer[1024];
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  return std::string(buffer);
}

int main(int argc, char const* argv[]) {
  std::cout << StrFormat("Hello %s", "World") << std::endl;
  return 0;
}
