#include <iostream>
#include <ctime>

using namespace std;

int level;

int seven(bool do_throw)
{
    if (do_throw)
        throw 7;
    else
        return 7;
}

int main()
{
    unsigned long count = 0;
    clock_t end = clock() + 5 * CLOCKS_PER_SEC;
    do
    {
        int sept = seven(false);
        ++count;
    } while (clock() < end);
    cout << "Plain return: " << count / 5 << " times per second.\n";
    count = 0;
    end = clock() + 5 * CLOCKS_PER_SEC;
    do
    {
        try
        {
            seven(true);
        }
        catch (int sept)
        {
            ++count;
        }
    } while (clock() < end);
    cerr << "Thrown return: " << count / 5 << " catches per second.\n";
    return 0;
}