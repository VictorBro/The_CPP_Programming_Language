#include <iostream>
#include <array>
#include <memory>
#include <ctime>

template <class T>
class Matrix
{
  std::array<int, 2> dim;
  T *elem;

public:
  Matrix(int d1, int d2) : dim{d1, d2}, elem{new T[d1 * d2]} {}
  int size() const { return dim[0] * dim[1]; }

  Matrix(const Matrix &);
  Matrix &operator=(const Matrix &);

  Matrix(Matrix &&);
  Matrix &operator=(Matrix &&);

  ~Matrix() { delete[] elem; }
};

template <class T>
Matrix<T>::Matrix(const Matrix &m) : dim{m.dim}, elem{new T[m.size()]{}}
{
  std::uninitialized_copy(m.elem, m.elem + m.size(), elem);
}

template <class T>
Matrix<T> &Matrix<T>::operator=(const Matrix &m)
{
  if (dim[0] != m.dim[0] || dim[1] != dim[1])
    throw std::runtime_error("bad size in Matrix = ");

  Matrix tmp{m};
  swap(tmp, *this);
  return *this;
}

template <class T>
Matrix<T>::Matrix(Matrix &&a) : dim{a.dim}, elem{a.elem}
{
  a.dim = {0, 0};
  a.elem = nullptr;
}

template <class T>
Matrix<T> &Matrix<T>::operator=(Matrix &&a)
{
  swap(dim, a.dim);
  swap(elem, a.elem);
  return *this;
}

int main()
{
  clock_t begin, end;
  double time_spent;
  Matrix<std::string> mat1{1000, 1000};

  begin = clock();
  Matrix<std::string> mat2{mat1};
  end = clock();
  time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
  std::cout << "Time taken by qsort = " << time_spent << "\n";

  begin = clock();
  Matrix<std::string> mat3 = std::move(mat2);
  end = clock();
  time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
  std::cout << "Time taken by qsort = " << time_spent << "\n";
}