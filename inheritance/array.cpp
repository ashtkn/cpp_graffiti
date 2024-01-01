#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct MyInterface {
  virtual ~MyInterface() = default;
  virtual void Print() const = 0;
};

class MyClassA : public MyInterface {
 public:
  void Print() const override { std::cout << msg_ << std::endl; }

 private:
  std::string msg_{"MyClassA"};
};

class MyClassB : public MyInterface {
 public:
  void Print() const override { std::cout << msg_ << std::endl; }

 private:
  std::string msg_{"MyClassB"};
};

int main() {
  {
    // Compile error
    // std::vector<MyInterface> v;
    // v.push_back(MyClassA());
    // v.push_back(MyClassB());
    // for (const auto& e : v) {
    //   e.Print();
    // }
  }

  {
    std::vector<std::unique_ptr<MyInterface>> v;
    v.push_back(std::make_unique<MyClassA>());
    v.push_back(std::make_unique<MyClassB>());
    for (const auto& e : v) {
      e->Print();
    }
  }

  return 0;
}
