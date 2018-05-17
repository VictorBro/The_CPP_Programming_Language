#include <iostream>
#include <chrono>

using namespace std;

int foo(bool b)
{
    int result = 100;
    if (b)
        throw result;
    return result;
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    try
    {
        foo(false);
    }
    catch (int e)
    {
        cerr << "exception thrown\n";
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    cerr << "took " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " to run.\n";

    start_time = std::chrono::high_resolution_clock::now();
    try
    {
        foo(true);
    }
    catch (int e)
    {
         cerr << "exception thrown\n";
    }
    end_time = std::chrono::high_resolution_clock::now();
    time = end_time - start_time;
    cerr << "took " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " to run.\n";
}