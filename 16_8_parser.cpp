#include "16_8_parser_impl.h"
#include "16_8_math.h"
#include "16_8_table.h"
#include "16_8_lexer.h"
#include "16_8_error.h"

using lexer::ts;
using lexer::Kind;

double parser::expr(bool get)
{
    double left = term(get);

    for (;;)
    {
        switch (ts.current().kind)
        {
        case Kind::plus:
        {
            auto d = term(true);
            left = math::my_plus(left, d);
            break;
        }
        case Kind::minus:
        {
            auto d = term(true);
            left = math::my_minus(left, d);
            break;
        }
        default:
            return left;
        }
    }
}

double parser::term(bool get)
{
    double left = prim(get);

    for (;;)
    {
        switch (ts.current().kind)
        {
        case Kind::mul:
        {
            auto d = prim(true);
            left = math::my_multiply(left, d);
            break;
        }
        case Kind::div:
        {
            auto d = prim(true);
            left = math::my_divide(left, d);
            break;
        }
        default:
            return left;
        }
    }
}

double parser::prim(bool get)
{
    if (get)
        ts.get();

    switch (ts.current().kind)
    {
    case Kind::number:
    {
        double v = ts.current().number_value;
        ts.get();
        return v;
    }
    case Kind::name:
    {
        double &v = table::table[ts.current().string_value];
        if (ts.get().kind == Kind::assign)
        {
            v = expr(true);
        }
        return v;
    }
    case Kind::minus:
        return -prim(true);
    case Kind::lp:
    {
        auto e = expr(true);
        if (ts.current().kind != Kind::rp)
        {
            throw std::invalid_argument{"line " + std::to_string(error::line_count.current()) + ": ')' expected"};
        }
        ts.get();
        return e;
    }
    default:
        throw std::invalid_argument{"line " + std::to_string(error::line_count.current()) + ": primary expected"};
    }
}