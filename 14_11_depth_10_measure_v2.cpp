#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int level;

void f_without_string(int throw_level)
{
    ++level;
    if (throw_level == level)
        throw level;
    else
        f_without_string(throw_level);
}

void f_with_string(int throw_level)
{
    string s;
    ++level;
    if (throw_level == level)
        throw level;
    else
        f_with_string(throw_level);
}

int main(int argc, char *argv[])
{
    int throw_level = (argc < 2 || atoi(argv[1]) < 1) ? 0 : atoi(argv[1]);
    unsigned long catch_count = 0;
    clock_t end = clock() + 5 * CLOCKS_PER_SEC;

    do
    {
        level = 0;
        try
        {
            if (throw_level == 0)
                throw 0;
            else
                f_without_string(throw_level);
        }
        catch (int depth)
        {
            ++catch_count;
        }
    } while (clock() < end);
    cout << "Without string: " << catch_count / 5 << "catches/second.\n";
    catch_count = 0;
    end = clock() + 5 * CLOCKS_PER_SEC;
    do
    {
        level = 0;
        try
        {
            if (throw_level == 0)
                throw 0;
            else
                f_with_string(throw_level);
        }
        catch (int depth)
        {
            ++catch_count;
        }
    } while (clock() < end);
    cout << "With string: " << catch_count / 5 << "catches/second.\n";
    return 0;
}