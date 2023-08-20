#include <stdexcept>
#include <iostream>
#include <cstring>

class BigInt
{
public:
  BigInt();
  BigInt(size_t n);

  BigInt(const BigInt &);
  BigInt &operator=(const BigInt &);

  BigInt(BigInt &&x);
  BigInt &operator=(BigInt &&x);

  ~BigInt()
  {
    if (short_max < sz)
      delete[] ptr;
  }

  char &operator[](int n) { return ptr[n]; }
  char operator[](int n) const { return ptr[n]; }

  BigInt &append(char c);
  BigInt &operator*=(size_t x);

  char *c_str() { return ptr; }
  const char *c_str() const { return ptr; }

  int size() const { return sz; }
  int capacity() const { return (sz <= short_max) ? short_max : sz + space; }

private:
  static const int short_max = 15;
  size_t sz;
  char *ptr;
  union {
    int space;
    char ch[short_max + 1];
  };

  void copy_from(const BigInt &x);
  void move_from(BigInt &x);
};

char *expand(const char *ptr, int n)
{
  char *p = new char[n];
  strcpy(p, ptr);
  return p;
}

void BigInt::copy_from(const BigInt &x)
{
  if (x.sz <= short_max)
  {
    memcpy(this, &x, sizeof(x));
    ptr = ch;
  }
  else
  {
    ptr = expand(x.ptr, x.sz + 1);
    sz = x.sz;
    space = 0;
  }
}

void BigInt::move_from(BigInt &x)
{
  if (x.sz <= short_max)
  {
    memcpy(this, &x, sizeof(x));
    ptr = ch;
  }
  else
  {
    ptr = x.ptr;
    sz = x.sz;
    space = x.space;
    x.ptr = x.ch;
    x.sz = 0;
    x.ch[0] = 0;
  }
}

BigInt::BigInt() : sz{0}, ptr{ch}
{
  ch[0] = 0;
}

size_t count_digits(size_t n)
{
  size_t count = 0;
  while (n > 0)
  {
    ++count;
    n = n / 10;
  }
  return count;
}

BigInt::BigInt(size_t n)
{
  sz = count_digits(n);
  ptr = (sz <= short_max) ? ch : new char[sz + 1];
  space = 0;

  int i = 0;
  while (n > 0)
  {
    ptr[i++] = '0' + (n % 10);
    n = n / 10;
  }
  ptr[i] = '\0';
}

BigInt::BigInt(const BigInt &x)
{
  std::cout << "in copy constructor\n";
  copy_from(x);
}

BigInt::BigInt(BigInt &&x)
{
  std::cout << "in move constructor\n";
  move_from(x);
}

BigInt &BigInt::operator=(const BigInt &x)
{
  std::cout << "in assignement\n";
  if (this == &x)
    return *this;
  char *p = (short_max < sz) ? ptr : 0;
  copy_from(x);
  delete[] p;
  return *this;
}

BigInt &BigInt::operator=(BigInt &&x)
{
  std::cout << "in move assignement\n";
  if (this == &x)
    return *this;
  if (short_max < sz)
    delete[] ptr;
  move_from(x);
  return *this;
}

BigInt &BigInt::append(char c)
{
  if (sz == short_max)
  {
    int n = sz + sz + 2;
    ptr = expand(ptr, n);
    space = n - sz - 2;
  }
  else if (short_max < sz)
  {
    if (space == 0)
    {
      int n = sz + sz + 2;
      char *p = expand(ptr, n);
      delete[] ptr;
      ptr = p;
      space = n - sz - 2;
    }
    else
      --space;
  }

  ptr[sz] = c;
  ptr[++sz] = 0;

  return *this;
}

BigInt &BigInt::operator*=(size_t x)
{
  int carry = 0;
  int product = 0;
  for (size_t i = 0; i < sz; ++i)
  {
    product = (ptr[i] - '0') * x;
    product += carry;
    ptr[i] = '0' + (product % 10);
    carry = product / 10;
  }
  if (carry)
  {
    while (carry > 0)
    {
      append('0' + carry % 10);
      carry /= 10;
    }
  }
  return *this;
}

std::ostream &operator<<(std::ostream &os, const BigInt &s)
{
  for (int i = s.size() - 1; i >= 0; --i)
  {
    os << s[i];
    if (i > 0 && i % 3 == 0)
      os << ',';
  }
  return os;
}

BigInt factorial(size_t n)
{
  BigInt fact{1};
  for (size_t i = 2; i <= n; ++i)
  {
    fact *= i;
  }
  return fact;
}

int main()
{
  BigInt x = factorial(1000);
  std::cout << x << std::endl;
}
