#include <iostream>

void func1(char *, int &);

using Pfunc = void (*)(char *, int &);
Pfunc pfunc1;

void func2(Pfunc pfunc1);
Pfunc func3(void);

Pfunc func4(Pfunc pfunc1)
{
    return pfunc1;
}

int main()
{
}