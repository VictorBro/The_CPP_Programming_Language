#ifndef ERROR_H
#define ERROR_H

#include <string>

namespace error
{

struct LineCount
{
    LineCount() : line_(1) {}

    unsigned long current()
    {
        return line_;
    }

    void new_line()
    {
        ++line_;
    }

  private:
    unsigned long line_;
};

extern LineCount line_count;
extern int no_of_errors;
double error(const std::string &);
}

#endif