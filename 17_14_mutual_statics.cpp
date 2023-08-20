#include <iostream>

class class2;

class class1
{
  public:
    static int n1;
};

class class2
{
  public:
    static int n2;
};

int class1::n1 = class2::n2;
int class2::n2 = class1::n1; 

int main()
{
    std::cout << "Hello, world!\n";
}