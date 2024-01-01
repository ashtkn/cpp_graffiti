#include <iostream>
#include <memory>
#include <string>

struct MyInterface {
  virtual ~MyInterface() = default;
  virtual void Print() const = 0;
};

class MySuperClass : public MyInterface {
 public:
  ~MySuperClass() override = default;
  void Print() const override { std::cout << msg_ << std::endl; }

 private:
  std::string msg_{"MySuperClass"};
};

class MySubClass : public MySuperClass {
 public:
  ~MySubClass() override = default;
  void Print() const override { std::cout << msg_ << std::endl; }

 private:
  std::string msg_{"MySubClass"};
};

template <typename U, typename T>
std::unique_ptr<U> dynamic_unique_cast(std::unique_ptr<T>&& ptr) {
  return std::unique_ptr<U>(dynamic_cast<U*>(ptr.release()));
}

// Compile error
// MyInterface MakeObject_Stack_Interface() {
//   auto ret = MySubClass();
//   return ret;
// }

MySuperClass MakeObject_Stack_SuperClass() {
  auto ret = MySubClass();
  return ret;
}

MySubClass MakeObject_Stack_SubClass() {
  auto ret = MySubClass();
  return ret;
}

std::unique_ptr<MyInterface> MakeObject_Heap_Interface() {
  auto ret = std::make_unique<MySubClass>();
  return ret;
}

std::unique_ptr<MySuperClass> MakeObject_Heap_SuperClass() {
  auto ret = std::make_unique<MySubClass>();
  return ret;
}

std::unique_ptr<MySubClass> MakeObject_Heap_SubClass() {
  auto ret = std::make_unique<MySubClass>();
  return ret;
}

int main() {
  // 元となる関数がコンパイルエラー
  // std::cout << "MakeObject_Stack_Interface" << std::endl;

  std::cout << "MakeObject_Stack_SuperClass" << std::endl;
  {
    auto o = MakeObject_Stack_SuperClass();
    o.Print();
    // static_cast<MySubClass>(o).Print(); // Compile error
    static_cast<MySubClass*>(&o)->Print();
    // dynamic_cast<MySubClass*>(&o)->Print(); // Segmentation fault
  }

  std::cout << "MakeObject_Stack_SubClass" << std::endl;
  {
    auto o = MakeObject_Stack_SubClass();
    o.Print();
    static_cast<MySubClass>(o).Print();      // 意味のないキャスト
    static_cast<MySubClass*>(&o)->Print();   // 意味のないキャスト
    dynamic_cast<MySubClass*>(&o)->Print();  // 意味のないキャスト
  }

  std::cout << "MakeObject_Heap_Interface" << std::endl;
  {
    auto o = MakeObject_Heap_Interface();
    o->Print();
    static_cast<MySubClass*>(o.get())->Print();
    dynamic_cast<MySubClass*>(o.get())->Print();

    auto o1 = dynamic_unique_cast<MySubClass>(std::move(o));
    o1->Print();
  }

  std::cout << "MakeObject_Heap_SuperClass" << std::endl;
  {
    auto o = MakeObject_Heap_SuperClass();
    o->Print();
    static_cast<MySubClass*>(o.get())->Print();
    dynamic_cast<MySubClass*>(o.get())->Print();

    auto o1 = dynamic_unique_cast<MySubClass>(std::move(o));
    o1->Print();
  }

  std::cout << "MakeObject_Heap_SubClass" << std::endl;
  {
    auto o = MakeObject_Heap_SubClass();
    o->Print();
    static_cast<MySubClass*>(o.get())->Print();   // 意味のないキャスト
    dynamic_cast<MySubClass*>(o.get())->Print();  // 意味のないキャスト
  }

  return 0;
}
