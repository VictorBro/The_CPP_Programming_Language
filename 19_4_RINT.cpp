#include <iostream>

namespace my_rint
{
class RINT
{
public:
  RINT(int n = 0) : i{n} {}
  RINT &operator+=(const RINT &);
  RINT &operator*=(const RINT &);
  RINT &operator/=(const RINT &);
  RINT &operator%=(const RINT &);
  RINT operator+() const;
  RINT operator-() const;

  int get_i() const { return i; }

private:
  int i;
};

RINT operator+(const RINT &, const RINT &);
RINT operator-(const RINT &, const RINT &);
RINT operator*(const RINT &, const RINT &);
RINT operator/(const RINT &, const RINT &);
RINT operator%(const RINT &, const RINT &);
inline std::ostream &operator<<(std::ostream &os, const RINT &a) { return os << a.get_i(); }

} // namespace my_rint

my_rint::RINT &my_rint::RINT::operator+=(const my_rint::RINT &rint)
{
  i += rint.i;
  return *this;
}

my_rint::RINT &my_rint::RINT::operator*=(const my_rint::RINT &rint)
{
  i *= rint.i;
  return *this;
}

my_rint::RINT &my_rint::RINT::operator/=(const my_rint::RINT &rint)
{
  if (rint.i == 0)
    throw std::runtime_error("Divide by zero");
  i /= rint.i;
  return *this;
}

my_rint::RINT &my_rint::RINT::operator%=(const my_rint::RINT &rint)
{
  if (rint.i == 0)
    throw std::runtime_error("Modulo by zero");
  i %= rint.i;
  return *this;
}

my_rint::RINT my_rint::operator+(const my_rint::RINT &a, const my_rint::RINT &b)
{
  RINT temp{a};
  return temp += b;
}

my_rint::RINT my_rint::RINT::operator+() const
{
  return *this;
}

my_rint::RINT my_rint::RINT::operator-() const
{
  return RINT{-(this->i)};
}

my_rint::RINT my_rint::operator-(const my_rint::RINT &a, const my_rint::RINT &b)
{
  RINT temp{a};
  return temp += -b;
}

my_rint::RINT my_rint::operator*(const my_rint::RINT &a, const my_rint::RINT &b)
{
  RINT temp{a};
  return temp *= b;
}

my_rint::RINT my_rint::operator/(const my_rint::RINT &a, const my_rint::RINT &b)
{
  RINT temp{a};
  return temp /= b;
}

my_rint::RINT my_rint::operator%(const my_rint::RINT &a, const my_rint::RINT &b)
{
  RINT temp{a};
  return temp %= b;
}

int main()
{
  my_rint::RINT myint;
  my_rint::RINT myint1 = 7;
  myint = myint + 2;
  std::cout << myint << std::endl; // Built in int+int
  std::cout << myint + myint1 << std::endl;
  std::cout << 2 + myint1 << std::endl;
  std::cout << +myint << std::endl;
  std::cout << -myint << std::endl;
  std::cout << myint - myint << std::endl;
  std::cout << myint * 2 << std::endl;
  std::cout << 3 * myint1 << std::endl;
  std::cout << myint * myint1 << std::endl;

  my_rint::RINT division;
  try
  {
    division = myint / 0;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << std::endl;
  }

  try
  {
    division = myint % 0;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << std::endl;
  }

  try
  {
    division = myint1 % myint;
    std::cout << division << std::endl;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << std::endl;
  }
}