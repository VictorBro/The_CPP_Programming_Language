#include <iostream>

using namespace std;

template <typename F>
struct Callback
{
    Callback(F f) : callback_func{f} {}
    void operator()() { callback_func(); }
    F callback_func;
};

template <class F>
Callback<F> set_callback(F f)
{
    return Callback<F>(f);
}

int main()
{
    auto act = set_callback([] { cout << "hello every body\n"; });
    act();
}