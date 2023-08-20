#include <iostream>
#include <memory>

class Foo
{
public:
  std::shared_ptr<int> p;

  Foo() : p{new int{}}
  {
    std::cout << "Default constructor\n";
  }

  Foo(int x) : p{new int{x}}
  {
    std::cout << "Constructor with 1 arg\n";
  }
};

int main()
{
  Foo fnew{3};
  std::cout << *fnew.p << '\n';
  std::cout << fnew.p.use_count() << '\n';
  {
    Foo fnew1{fnew};
    std::cout << fnew.p.use_count() << '\n';
  }
  std::cout << fnew.p.use_count() << '\n';
}