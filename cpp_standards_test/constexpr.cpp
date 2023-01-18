#include <string>
#include <vector>

namespace {
// C++17以降でコンパイル可能
// constexpr std::string s("Hello, World!"); // コンパイル不可
constexpr std::string_view s_view = "Hello world";
// constexpr std::vector<int> v{1, 2, 3, 4, 5}; // コンパイル不可
}  // namespace

int main() { return 0; }
