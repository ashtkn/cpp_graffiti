#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>

struct C1 {
  // トリビアルなデストラクタを持っている
  ~C1() = default;

  // 特殊関数ではないメンバ関数は持っている
  int f(int x) const { return x; }
};

struct C2 {
  // 非トリビアルなデストラクタを持っている
  ~C2() {}
};

// 組み込み型は全てトリビアルに破棄可能
static_assert(std::is_trivially_destructible<int>::value == true, "int is trivially destructible");
static_assert(std::is_trivially_destructible<int*>::value == true, "int* is trivially destructible");
static_assert(std::is_trivially_destructible<const char*>::value == true, "const char* is trivially destructible");

// ユーザー定義型は、ユーザー定義のデストラクタを持っていなければトリビアルに破棄可能
static_assert(std::is_trivially_destructible<C1>::value == true, "C1 is trivially destructible");
static_assert(std::is_trivially_destructible<C2>::value == false, "C2 isn't trivially destructible");

// 標準ライブラリ（トリビアルに破棄可能）
static_assert(std::is_trivially_destructible<std::string_view>::value == true, "std::string_view is trivially destructible");

// 標準ライブラリ（型引数次第でトリビアルに破棄可能かどうかが変化する）
static_assert(std::is_trivially_destructible<std::array<C1, 5>>::value == true, "std::array<C1, N> is trivially destructible");
static_assert(std::is_trivially_destructible<std::array<C2, 5>>::value == false, "std::array<C2, N> isn't trivially destructible");
static_assert(std::is_trivially_destructible<std::optional<C1>>::value == true, "std::optional<C1> is trivially destructible");
static_assert(std::is_trivially_destructible<std::optional<C2>>::value == false, "std::optional<C2> isn't trivially destructible");
static_assert(std::is_trivially_destructible<std::tuple<int, C1>>::value == true, "std::tuple<int, C1> is trivially destructible");
static_assert(std::is_trivially_destructible<std::tuple<int, C2>>::value == false, "std::tuple<int, C2> isn't trivially destructible");

// 標準ライブラリ（トリビアルに破棄可能でない）
static_assert(std::is_trivially_destructible<std::map<int, int>>::value == false, "std::map<int, int> isn't trivially destructible");
static_assert(std::is_trivially_destructible<std::unique_ptr<int>>::value == false, "std::unique_ptr<int> isn't trivially destructible");
static_assert(std::is_trivially_destructible<std::string>::value == false, "std::string isn't trivially destructible");
static_assert(std::is_trivially_destructible<std::unordered_map<int, int>>::value == false, "std::unordered_map<int, int> isn't trivially destructible");
static_assert(std::is_trivially_destructible<std::vector<int>>::value == false, "std::vector<int> isn't trivially destructible");

int main() { return 0; }
