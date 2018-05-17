#include <iostream>

using namespace std;

int main()
{
    try
    {
        throw runtime_error{"haha"};
    }
    catch (const std::range_error &)
    {
        cout << "range error\n";
    }
    catch (...)
    {
        cout << "some error\n";
    }
}