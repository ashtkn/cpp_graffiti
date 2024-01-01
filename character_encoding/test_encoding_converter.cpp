#include <iostream>
#include <string>

#include "encoding_converter.h"

int main() {
  std::string u8_str(u8"大塩平八郎のLAN");
  std::cout << u8_str << std::endl;

  {
    auto u16_str = encoding_converter::ConvU8ToU16(u8_str).value();
    for (auto c : u16_str) {
      std::cout << c << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
