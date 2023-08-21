#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string s{u8"大塩平八郎のLAN"};
  std::cout << s << ": " << s.length() << std::endl;

  std::vector<std::string> v;
  v.push_back(u8"大");
  v.push_back(u8"塩");
  v.push_back(u8"平");
  v.push_back(u8"八");
  v.push_back(u8"郎");
  v.push_back(u8"の");
  v.push_back(u8"LAN");

  for (const auto& e : v) {
    std::cout << e << ": " << e.length() << std::endl;
  }

  size_t pos{0u};
  for (const auto& e : v) {
    std::cout << s.substr(pos, e.length()) << ": " << e.length() << std::endl;
    pos += e.length();
  }

  return 0;
}
