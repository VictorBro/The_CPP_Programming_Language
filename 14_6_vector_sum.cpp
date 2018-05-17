#include <memory>
#include <iostream>

using namespace std;

template <class T, class A = std::allocator<T>>
struct vector_base
{
    A alloc;  // allocator
    T *elem;  // start of allocation
    T *space; // end of element sequence, start of space allocated for possible expansion
    T *last;  // end of allocated space

    vector_base(const A &a, typename A::size_type n)
        : alloc{a}, elem{alloc.allocate(n)}, space{elem + n}, last{elem + n} {}
    ~vector_base() { alloc.deallocate(elem, last - elem); }

    vector_base(const vector_base &) = delete;
    vector_base &operator=(const vector_base &) = delete;

    vector_base(vector_base &&);
    vector_base &operator=(vector_base &&);
};

template <class T, class A>
vector_base<T, A>::vector_base(vector_base &&a)
    : alloc{a.alloc},
      elem{a.elem},
      space{a.space},
      last{a.space}
{
    a.elem = a.space = a.last = nullptr;
}

template <class T, class A>
vector_base<T, A> &vector_base<T, A>::operator=(vector_base &&a)
{
    swap(*this, a);
    return *this;
}

struct my_out_of_range
{
};

template <class T, class A = std::allocator<T>>
class vector
{
    vector_base<T, A> vb;
    void destroy_elements();

  public:
    using size_type = unsigned int;
    explicit vector(size_type n, const T &val = T(), const A & = A());

    vector(const vector &a);
    vector &operator=(const vector &a);

    vector(vector &&a);
    vector &operator=(vector &&a);

    T &operator[](size_type n);

    size_type size() const { return vb.space - vb.elem; }
    size_type capacity() const { return vb.last - vb.elem; }

    void reserve(size_type);

    void resize(size_type, const T & = {});
    void clean() { resize(0); }
    void push_back(const T &);
};

template <class T, class A>
void vector<T, A>::destroy_elements()
{
    for (T *p = vb.elem; p != vb.space; ++p)
        p->~T();
    vb.space = vb.elem;
}

template <class T, class A>
vector<T, A>::vector(size_type n, const T &val, const A &a)
    : vb{a, n}
{
    uninitialized_fill(vb.elem, vb.elem + n, val);
}

template <class T, class A>
vector<T, A>::vector(const vector<T, A> &a)
    : vb{a.alloc, a.size()}
{
    uninitialized_copy(a.begin(), a.end(), vb.elem);
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(const vector<T, A> &a)
{
    if (capacity() < a.size())
    {
        vector temp{a};
        swap(*this, temp);
        return *this;
    }
    if (this == &a)
        return *this;

    size_type sz = size();
    size_type asz = a.size();
    vb.alloc = a.vb.alloc;
    if (asz <= sz)
    {
        copy(a.begin(), a.begin() + asz, vb.elem);
        for (T *p = vb.elem + asz; p != vb.space; ++p)
            p->~T();
    }
    else
    {
        copy(a.begin(), a.begin() + sz, vb.elem);
        uninitialized_copy(a.begin() + sz, a.end(), vb.space);
    }
    vb.space = vb.elem + asz;
    return *this;
}

template <class T, class A>
vector<T, A>::vector(vector &&a)
    : vb{move(a.vb)}
{
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(vector &&a)
{
    clean();
    swap(*this, a);
    return *this;
}

template <class T, class A>
T &vector<T, A>::operator[](size_type n)
{
    if (size() <= n)
        throw my_out_of_range();
    return vb.elem[n];
}

template <typename In, typename Out>
Out uninitialized_move(In b, In e, Out oo)
{
    for (; b != e; ++b, ++oo)
    {
        new (static_cast<void *>(&*oo)) In{move(*b)};
        b->~In();
    }
    return b;
}

template <class T, class A>
void vector<T, A>::reserve(size_type newalloc)
{
    if (newalloc <= capacity())
        return;
    vector_base<T, A> b{vb.alloc, newalloc};
    uninitialized_move(vb.elem, vb.elem + size(), b.elem);
    swap(vb, b);
}

template <typename In>
void destroy(In b, In e)
{
    for (; b != e; ++b)
        b->~In();
}

template <class T, class A>
void vector<T, A>::resize(size_type newsize, const T &val)
{
    reserve(newsize);
    if (size() < newsize)
        uninitialized_fill(vb.elem + size(), vb.elem + newsize, val);
    else
        destroy(vb.elem + size(), vb.elem + newsize);
    vb.space = vb.last = vb.elem + newsize;
}

template <class T, class A>
void vector<T, A>::push_back(const T &val)
{
    if (capacity() == size())
        reserve(capacity() ? 2 * capacity() : 8);
    vb.alloc.construct(&vb.elem[size()], val);
    ++vb.space;
}

/* It's bad idea because we use 
   exception handling mechanism for normal flow */
int main()
{
    int sum = 0;

    try
    {
        vector<int> v(5, 7);
        int i = 0;

        while (true)
        {
            sum += v[i];
            ++i;
        }
    }
    catch (my_out_of_range)
    {
        cout << sum << '\n';
    }
}