#include <iostream>

namespace my_rint
{
class INT
{
public:
  INT(int n = 0) : i{n} {}
  INT &operator+=(const INT &);
  INT operator-() const;
  int get_i() const { return i; }

private:
  int i;
};

INT operator+(const INT &, const INT &);
INT operator-(const INT &, const INT &);
inline std::ostream &operator<<(std::ostream &os, const INT &a) { return os << a.get_i(); }

} // namespace my_rint

my_rint::INT &my_rint::INT::operator+=(const my_rint::INT &rint)
{
  i += rint.i;
  return *this;
}

my_rint::INT my_rint::operator+(const my_rint::INT &a, const my_rint::INT &b)
{
  INT temp{a};
  return temp += -b;
}

my_rint::INT my_rint::INT::operator-() const
{
  return INT{-(this->i)};
}

my_rint::INT my_rint::operator-(const my_rint::INT &a, const my_rint::INT &b)
{
  INT temp{a};
  return temp += b;
}

#define int my_rint::INT
main()
{
  int x = 3;
  int y = 1;
  int z = x - y;
  std::cout << z;

  std::cout << std::endl;

  std::cout << x + y;
  
  std::cout << std::endl;
}