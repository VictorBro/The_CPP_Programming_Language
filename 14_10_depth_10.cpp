#include <iostream>

using namespace std;

void ten()
{
    throw runtime_error{"haha"};
}

void nine()
{
    try
    {
        ten();
    }
    catch (const runtime_error &e)
    {
        cerr << "9\n";
        throw;
    }
}

void eight()
{
    try
    {
        nine();
    }
    catch (const runtime_error &e)
    {
        cerr << "8\n";
        throw;
    }
}

void seven()
{
    try
    {
        eight();
    }
    catch (const runtime_error &e)
    {
        cerr << "7\n";
        throw;
    }
}

void six()
{
    try
    {
        seven();
    }
    catch (const runtime_error &e)
    {
        cerr << "6\n";
        throw;
    }
}

void five()
{
    try
    {
        six();
    }
    catch (const runtime_error &e)
    {
        cerr << "5\n";
        throw;
    }
}

void four()
{
    try
    {
        five();
    }
    catch (const runtime_error &e)
    {
        cerr << "4\n";
        throw;
    }
}

void three()
{
    try
    {
        four();
    }
    catch (const runtime_error &e)
    {
        cerr << "3\n";
        throw;
    }
}

void two()
{
    try
    {
        three();
    }
    catch (const runtime_error &e)
    {
        cerr << "2\n";
        throw;
    }
}

void one()
{
    try
    {
        two();
    }
    catch (const runtime_error &e)
    {
        cerr << "1\n";
        throw;
    }
}

int main()
{
    try
    {
        one();
    }
    catch (const runtime_error &e)
    {
        cerr << "0\n";
    }
}