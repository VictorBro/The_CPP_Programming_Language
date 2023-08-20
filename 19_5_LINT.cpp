#include <iostream>

namespace my_rint
{
class LINT
{
public:
  LINT(long long n = 0) : i{n} {}
  LINT &operator+=(const LINT &);
  LINT &operator*=(const LINT &);
  LINT &operator/=(const LINT &);
  LINT &operator%=(const LINT &);
  LINT operator+() const;
  LINT operator-() const;

  long long get_i() const { return i; }

private:
  long long i;
};

LINT operator+(const LINT &, const LINT &);
LINT operator-(const LINT &, const LINT &);
LINT operator*(const LINT &, const LINT &);
LINT operator/(const LINT &, const LINT &);
LINT operator%(const LINT &, const LINT &);
inline std::ostream &operator<<(std::ostream &os, const LINT &a) { return os << a.get_i(); }

} // namespace my_rint

my_rint::LINT &my_rint::LINT::operator+=(const my_rint::LINT &rint)
{
  i += rint.i;
  return *this;
}

my_rint::LINT &my_rint::LINT::operator*=(const my_rint::LINT &rint)
{
  i *= rint.i;
  return *this;
}

my_rint::LINT &my_rint::LINT::operator/=(const my_rint::LINT &rint)
{
  if (rint.i == 0)
    throw std::runtime_error("Divide by zero");
  i /= rint.i;
  return *this;
}

my_rint::LINT &my_rint::LINT::operator%=(const my_rint::LINT &rint)
{
  if (rint.i == 0)
    throw std::runtime_error("Modulo by zero");
  i %= rint.i;
  return *this;
}

my_rint::LINT my_rint::operator+(const my_rint::LINT &a, const my_rint::LINT &b)
{
  LINT temp{a};
  return temp += b;
}

my_rint::LINT my_rint::LINT::operator+() const
{
  return *this;
}

my_rint::LINT my_rint::LINT::operator-() const
{
  return LINT{-(this->i)};
}

my_rint::LINT my_rint::operator-(const my_rint::LINT &a, const my_rint::LINT &b)
{
  LINT temp{a};
  return temp += -b;
}

my_rint::LINT my_rint::operator*(const my_rint::LINT &a, const my_rint::LINT &b)
{
  LINT temp{a};
  return temp *= b;
}

my_rint::LINT my_rint::operator/(const my_rint::LINT &a, const my_rint::LINT &b)
{
  LINT temp{a};
  return temp /= b;
}

my_rint::LINT my_rint::operator%(const my_rint::LINT &a, const my_rint::LINT &b)
{
  LINT temp{a};
  return temp %= b;
}

int main()
{
  my_rint::LINT myint;
  my_rint::LINT myint1 = 7;
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

  my_rint::LINT division;
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