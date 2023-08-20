#ifndef LEXER_H
#define LEXER_H

#include <string>

namespace lexer
{

enum class Kind : char
{
    name,
    number,
    end,
    plus = '+',
    minus = '-',
    mul = '*',
    div = '/',
    print = ';',
    assign = '=',
    lp = '(',
    rp = ')'
};

struct Token
{
    Kind kind;
    std::string string_value;
    double number_value;
};

class Token_stream
{
  public:
    Token_stream(std::istream &s) : ip{&s}, owns{false} {}
    Token_stream(std::istream *p) : ip{p}, owns{true} {}

    ~Token_stream()
    {
        close();
    }

    Token get();
    Token &current()
    {
        return ct;
    }

    void set_input(std::istream &s)
    {
        close();
        ip = &s;
        owns = false;
    }

    void set_input(std::istream *p)
    {
        close();
        ip = p;
        owns = true;
    }

  private:
    void close()
    {
        if (owns)
        {
            delete ip;
        }
    }

    std::istream *ip;
    bool owns;
    Token ct{Kind::end};
};

extern Token_stream ts;
}

#endif
