#include <iostream>
#include <string>

#include "optional.h"

int main(int argc, char const* argv[]) {
  {
    const mylib::optional<int> o1;                  // default constructor
    const mylib::optional<int> o2(1);               // converting constructor
    const auto val = o2.value();             // value()
    const mylib::optional<int> o2_(val);            // converting constructor
    const mylib::optional<int> o3 = o2;             // copy assignment operator
    const mylib::optional<int> o4(o2);              // copy constructor
    const mylib::optional<int> o5 = std::move(o3);  // move assignment operator
    const mylib::optional<int> o6(std::move(o4));   // move constructor

    if (o1) {
    }
    if (o2) {
    }

    const bool b1 = o1.has_value();  // false
    const bool b2 = o2.has_value();  // true

    try {
      const int i1 = o1.value();  // throws
    } catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    mylib::optional<int> o1(1);
    int& i1 = o1.value();
    int&& i2 = mylib::optional<int>(1).value();
  }
  {
    mylib::optional<std::string> o1("");
    o1->push_back('a');

    const mylib::optional<std::string> o2("");
    o2->size();

    mylib::optional<std::string> o3("");
    (*o3).push_back('a');

    const mylib::optional<std::string> o4("");
    (*o4).size();
  }

  return 0;
}
