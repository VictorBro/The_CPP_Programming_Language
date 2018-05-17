#include <iostream>
#include <stdexcept>
#include <limits>
#include <cmath>

using namespace std;

double my_plus(double x, double y)
{
    if (y > 0.0 && x > numeric_limits<double>::max() - y)
    {
        throw overflow_error{"Overflow occured"};
    }
    else if (y < 0.0 && x < numeric_limits<double>::min() - y)
    {
        throw underflow_error{"underflow occured"};
    }
    return x + y;
}

double my_minus(double x, double y)
{
    return my_plus(x, -y);
}

double my_multiply(double x, double y)
{
    if (fabs(y) > 1.0 && fabs(x) > numeric_limits<double>::max() / fabs(y))
        throw overflow_error{"Overflow occured during multiplication"};

    double result = x * y;
    if (x != 0.0 && y != 0.0 && result == 0)
    {
        throw underflow_error{"underflow occured during multiplication"};
    }
    return result;
}

double my_divide(double x, double y)
{
    if (fabs(y) < 1.0 && fabs(x) > numeric_limits<double>::max() * fabs(y))
        throw overflow_error{"Overflow occured during division"};

    double result = x / y;
    if (x != 0.0 && result == 0)
    {
        throw underflow_error{"underflow occured during division"};
    }
    return result;
}

int main(int argc, char *argv[])
{
    try
    {
        my_divide(5, 0);
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << '\n';
    }
}