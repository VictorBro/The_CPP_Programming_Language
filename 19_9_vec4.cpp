#include <iostream>
#include <initializer_list>

class Vec4
{
public:
  Vec4(float x1 = 0, float x2 = 0, float x3 = 0, float x4 = 0)
      : arr{x1, x2, x3, x4}
  {
  }

  float &operator[](int n)
  {
    check(n);
    return arr[n];
  }

  float operator[](int n) const
  {
    check(n);
    return arr[n];
  }

  Vec4 &operator+=(const Vec4 &);

private:
  float arr[4];

  void check(int n) const
  {
    if (n < 0 || n >= 4)
      throw std::out_of_range("out of range");
  }
};

Vec4 &Vec4::operator+=(const Vec4 &vec)
{
  for (int i = 0; i < 4; ++i)
  {
    arr[i] += vec[i];
  }
  return *this;
}

Vec4 operator+(const Vec4 &vec1, const Vec4 &vec2)
{
  Vec4 res{vec1};
  res += vec2;
  return res;
}

int main()
{
  Vec4 my_vec1;
  Vec4 my_vec2{1, 2, 3, 4};

  for (int i = 0; i < 4; ++i)
  {
    std::cout << my_vec2[i] << " ";
  }
  std::cout << '\n';

  try
  {
    std::cout << my_vec1[5];
  }
  catch (const std::logic_error &e)
  {
    std::cerr << e.what() << '\n';
  }

  my_vec1[1] = 4;
  my_vec1[2] = 4;
  Vec4 res = my_vec1 + my_vec2;
  for (int i = 0; i < 4; ++i)
  {
    std::cout << res[i] << " ";
  }
  std::cout << '\n';
}