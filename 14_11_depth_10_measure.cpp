#include <iostream>
#include <chrono>

using namespace std;

struct my_runtime_error
{
    string s;
};

void ten(int b)
{
    try
    {
        if (b == 10)
            throw my_runtime_error{"haha"};
    }
    catch (const my_runtime_error &e)
    {
        cerr << "10\n";
        throw;
    }
}

void nine(int b)
{
    try
    {
        if (b == 9)
            throw my_runtime_error{"haha"};
        ten(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "9\n";
        throw;
    }
}

void eight(int b)
{
    try
    {
        if (b == 8)
            throw my_runtime_error{"haha"};
        nine(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "8\n";
        throw;
    }
}

void seven(int b)
{
    try
    {
        if (b == 7)
            throw my_runtime_error{"haha"};
        eight(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "7\n";
        throw;
    }
}

void six(int b)
{
    try
    {
        if (b == 6)
            throw my_runtime_error{"haha"};
        seven(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "6\n";
        throw;
    }
}

void five(int b)
{
    try
    {
        if (b == 5)
            throw my_runtime_error{"haha"};
        six(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "5\n";
        throw;
    }
}

void four(int b)
{
    try
    {
        if (b == 4)
            throw my_runtime_error{"haha"};
        five(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "4\n";
        throw;
    }
}

void three(int b)
{
    try
    {
        if (b == 3)
            throw my_runtime_error{"haha"};
        four(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "3\n";
        throw;
    }
}

void two(int b)
{
    try
    {
        if (b == 2)
            throw my_runtime_error{"haha"};
        three(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "2\n";
        throw;
    }
}

void one(int b)
{
    try
    {
        if (b == 1)
            throw my_runtime_error{"haha"};
        two(b);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "1\n";
        throw;
    }
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    try
    {
        one(0);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "0\n";
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    cerr << "took " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " to run.\n";

    start_time = std::chrono::high_resolution_clock::now();
    try
    {
        one(10);
    }
    catch (const my_runtime_error &e)
    {
        cerr << "0\n";
    }
    end_time = std::chrono::high_resolution_clock::now();
    time = end_time - start_time;
    cerr << "took " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " to run.\n";
}