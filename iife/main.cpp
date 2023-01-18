#include <iostream>
#include <sstream>
#include <string>

int main() {
  /*
   * 1. ラムダ式を用いた即時関数（C++11以降）
   */
  const std::string& s0 = [/* キャプチャする変数 */]() {
    std::stringstream ss;
    ss << "Lambda expression";  // 一時的な変数を用いた処理
    ss << " ("
       << "Immediately Invoked Function Expression"
       << ")";
    return ss.str();
  }();  // ()をつけてラムダ式を即時実行する
  std::cout << s0 << std::endl;
  // 以降，ラムダ式内で宣言された一時的な変数にはアクセスできない．また，文字列s0はconstなので誤って変更される恐れはない

  /*
   * 2.
   * ブロックを作って，一時的な変数へのアクセスを制限する方法（C++11以前も可）
   */
  std::string s1;
  {
    std::stringstream ss;
    ss << "Block";  // 一時的な変数を用いた処理
    s1 = ss.str();
  }
  std::cout << s1 << std::endl;
  // 以降，ブロック内で宣言された一時的な変数にはアクセスできないが，文字列s1が非constなので誤って変更される恐れがある

  /*
   * 3. ラムダ式を用いた即時関数もブロックも使わない場合
   */
  std::stringstream ss;
  ss << "No Block";  // 一時的な変数を用いた処理
  const std::string& s2 = ss.str();
  std::cout << s2 << std::endl;
  // 以降も使い終わったはずの一時的な変数（ss）にアクセスできてしまい，事故の原因になる

  return 0;
}
