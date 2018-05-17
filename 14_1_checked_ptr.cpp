#include <stdexcept>
#include <iostream>
#include <string>

template <class T>
class Checked_ptr
{
    T *begin;
    T *cur;
    T *end;

    void check(T *p) const;

  public:
    Checked_ptr(T *arr, size_t size, int ind)
        : begin{arr}, end{arr + size}, cur{arr + ind} {}

    Checked_ptr &operator++()
    {
        cur++;
        return *this;
    }
    Checked_ptr &operator--()
    {
        cur--;
        return *this;
    }
    Checked_ptr &operator+=(int i)
    {
        cur += i;
        return *this;
    }

    T &operator[](int i) const;
    T &operator*() const
    {
        check(cur);
        return *cur;
    }
};

template <class T>
void Checked_ptr<T>::check(T *p) const
{
    if (p < begin || p >= end)
        throw std::out_of_range("Out of range error");
}

template <class T>
T &Checked_ptr<T>::operator[](int i) const
{
    T *ptr = cur + i;
    check(ptr);
    return *ptr;
}

const int ARR_SIZE = 10;

int main()
{
    try
    {
        int arr[ARR_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        Checked_ptr<int> p(arr, ARR_SIZE, 0);
        std::cout << *p << '\n';
        ++p;
        std::cout << *p << '\n';
        //p += 20;
        //std::cout << *p << '\n';

        std::string str[3] = {"Hello", "world", "haha"};
        Checked_ptr<std::string> q(str, 3, 0);
        std::cout << (*q).size() << '\n';
        std::cout << q[2].size() << '\n';
        std::cout << q[5].size() << '\n';
    }
    catch (std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }
}