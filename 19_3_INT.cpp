#include <iostream>

class INT
{
public:
  INT(int n = 0) : i{n} {}
  operator int() { return i; }

private:
  int i;
};

int main()
{
  INT myint;
  INT myint1 = 7;
  myint = myint + 2;
  std::cout << myint << std::endl; // Built in int+int
  std::cout << myint + myint1 << std::endl;
}