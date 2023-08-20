#include <iostream>

class Hack
{
  public:
    Hack() { std::cout << "Initialize\n"; }
    ~Hack() { std::cout << "Clean up\n"; }
};

Hack hack;

int main()
{
    std::cout << "Hello, world!\n";
}