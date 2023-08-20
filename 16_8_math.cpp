#include "16_8_math.h"
#include <stdexcept>
#include <limits>

double math::my_plus(double x, double y)
{
    if (y > 0.0 && x > std::numeric_limits<double>::max() - y)
    {
        throw std::overflow_error{"Overflow occured"};
    }
    else if (y < 0.0 && x < std::numeric_limits<double>::min() - y)
    {
        throw std::underflow_error{"underflow occured"};
    }
    return x + y;
}

double math::my_minus(double x, double y)
{
    return my_plus(x, -y);
}

double math::my_multiply(double x, double y)
{
    if (fabs(y) > 1.0 && fabs(x) > std::numeric_limits<double>::max() / fabs(y))
        throw std::overflow_error{"Overflow occured during multiplication"};

    double result = x * y;
    if (x != 0.0 && y != 0.0 && result == 0)
    {
        throw std::underflow_error{"underflow occured during multiplication"};
    }
    return result;
}

double math::my_divide(double x, double y)
{
    if (fabs(y) < 1.0 && fabs(x) > std::numeric_limits<double>::max() * fabs(y))
        throw std::overflow_error{"Overflow occured during division"};

    double result = x / y;
    if (x != 0.0 && result == 0)
    {
        throw std::underflow_error{"underflow occured during division"};
    }
    return result;
}