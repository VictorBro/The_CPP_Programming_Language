#include "16_8_error.h"
#include <iostream>

error::LineCount line_count;
int no_of_errors;

double error::error(const std::string &s)
{
    ++no_of_errors;
    std::cerr << "ERROR (line " << line_count.current() << "): " << s << '\n';
    return 1;
}