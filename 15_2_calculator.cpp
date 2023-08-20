#include <iostream>

namespace X
{
    int i, j, k;
}

int k;

void f1()
{
    int i = 5;
    using namespace X; // make names from X accessible
    i++;               // local i
    std::cout << i << '\n';
    j++;               // X::j
    ::k++;             // the global k
    X::k++;            // X’s k
}

int main()
{
    f1();
}