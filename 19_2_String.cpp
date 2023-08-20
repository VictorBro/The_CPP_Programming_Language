#include <stdexcept>
#include <iostream>
#include <cstring>

class String
{
public:
  String();
  String(const char *p);

  String(const String &);
  String &operator=(const String &);

  String(String &&x);
  String &operator=(String &&x);

  ~String()
  {
    if (short_max < sz)
      delete[] ptr;
  }

  char &operator[](int n) { return ptr[n]; }
  char operator[](int n) const { return ptr[n]; }

  char &at(int n)
  {
    check(n);
    return ptr[n];
  }
  char at(int n) const
  {
    check(n);
    return ptr[n];
  }

  String &operator+=(char c);

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

  void check(int n) const
  {
    if (n < 0 || n >= sz)
      throw std::out_of_range("String::at()");
  }

  void copy_from(const String &x);
  void move_from(String &x);
};

char *expand(const char *ptr, int n)
{
  char *p = new char[n];
  strcpy(p, ptr);
  return p;
}

void String::copy_from(const String &x)
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

void String::move_from(String &x)
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

String::String() : sz{0}, ptr{ch}
{
  ch[0] = 0;
}

String::String(const char *p)
    : sz{strlen(p)},
      ptr{(sz <= short_max) ? ch : new char[sz + 1]},
      space{0}
{
  strcpy(ptr, p);
}

String::String(const String &x)
{
  copy_from(x);
}

String::String(String &&x)
{
  move_from(x);
}

String &String::operator=(const String &x)
{
  if (this == &x)
    return *this;
  char *p = (short_max < sz) ? ptr : 0;
  copy_from(x);
  delete[] p;
  return *this;
}

String &String::operator=(String &&x)
{
  if (this == &x)
    return *this;
  if (short_max < sz)
    delete[] ptr;
  move_from(x);
  return *this;
}

String &String::operator+=(char c)
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

std::ostream &operator<<(std::ostream &os, const String &s)
{
  return os << s.c_str();
}

std::istream &operator>>(std::istream &is, String &s)
{
  s = "";
  is >> std::ws;
  char ch = ' ';
  while (is.get(ch) && !isspace(ch))
    s += ch;
  return is;
}

bool operator==(const String &a, const String &b)
{
  if (a.size() != b.size())
    return false;
  for (int i = 0; i != a.size(); ++i)
    if (a[i] != b[i])
      return false;
  return true;
}

bool operator!=(const String &a, const String &b)
{
  return !(a == b);
}

char *begin(String &x)
{
  return x.c_str();
}

char *end(String &x)
{
  return x.c_str() + x.size();
}

const char *begin(const String &x)
{
  return x.c_str();
}

const char *end(const String &x)
{
  return x.c_str() + x.size();
}

String &operator+=(String &a, const String &b)
{
  for (auto x : b)
    a += x;
  return a;
}

String operator+(const String &a, const String &b)
{
  String res{a};
  res += b;
  return res;
}

String operator"" _s(const char *p, size_t)
{
  return String{p};
}

int main()
{
  String s{"abcdefghij"};
  std::cout << s << '\n';
  s += 'k';
  s += 'l';
  s += 'm';
  s += 'n';
  std::cout << s << '\n';
  String s2 = "Hell";
  s2 += " and high water";
  std::cout << s2 << '\n';
  String s3 = "qwerty";
  s3 = s3;
  String s4 = "the quick brown fox jumped over the lazy dog";
  s4 = s4;
  std::cout << s3 << " " << s4 << '\n';
  std::cout << s + ". " + s3 + String(". ") + "Horsefeathers\n";
  String buf;
  while (std::cin >> buf && buf != "quit")
    std::cout << buf << " " << buf.size() << " " << buf.capacity() << '\n';
}
