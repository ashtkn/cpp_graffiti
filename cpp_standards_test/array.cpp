#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace {

struct S {
  std::string str;
  size_t num;
};

}  // namespace

int main() {
  std::vector<S> v{};
  for (size_t i = 0; i < 10; ++i) {
    v.push_back({"", 0});
  }

  // Compile error
  // std::array<S, v.size()> arr {};

  auto ptr = std::make_unique<S[]>(v.size());

  return 0;
}
