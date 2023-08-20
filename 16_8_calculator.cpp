#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <cmath>
#include <limits>

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

LineCount line_count;
int no_of_errors;
double error(const std::string &);
}

namespace table
{

std::map<std::string, double> table;
}

namespace math
{

double my_plus(double, double);
double my_minus(double, double);
double my_multiply(double, double);
double my_divide(double, double);
}

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

Token_stream ts{std::cin};
}

namespace parser
{
using lexer::ts;
using lexer::Kind;

double expr(bool);
double term(bool);
double prim(bool);
}

namespace driver
{

void calculate(void);
}

lexer::Token lexer::Token_stream::get()
{
    char ch = 0;

    do
    {
        if (!ip->get(ch))
        {
            return ct = {Kind::end};
        }
    } while (ch != '\n' && isspace(ch));

    switch (ch)
    {
    case 0:
        return ct = {Kind::end};
    case '\n':
        error::line_count.new_line(); // fall through
    case ';':
        return ct = {Kind::print};
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
    case '=':
        return ct = {static_cast<Kind>(ch)};
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
        ip->putback(ch);
        *ip >> ct.number_value;
        ct.kind = Kind::number;
        return ct;
    default:
        if (isalpha(ch))
        {
            ct.string_value = ch;
            while (ip->get(ch) && isalnum(ch))
            {
                ct.string_value += ch;
            }
            ip->putback(ch);
            ct.kind = Kind::name;
            return ct;
        }
        throw std::invalid_argument{"line " + std::to_string(error::line_count.current()) + ": bad token"};
    }
}

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

double error::error(const std::string &s)
{
    ++no_of_errors;
    std::cerr << "ERROR (line " << line_count.current() << "): " << s << '\n';
    return 1;
}

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

void driver::calculate()
{
    for (;;)
    {
        lexer::ts.get();

        if (lexer::ts.current().kind == lexer::Kind::end)
        {
            break;
        }
        if (lexer::ts.current().kind == lexer::Kind::print)
        {
            continue;
        }
        std::cout << parser::expr(false) << '\n';
    }
}

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 1: // read from standard input
        break;
    case 2: // read from argument string
        try
        {
            auto iss = new std::istringstream{argv[1]};
            lexer::ts.set_input(iss);
        }
        catch (const std::bad_alloc &ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            return 1;
        }
        break;
    default:
        error::error("too many arguments");
        return 1;
    }

    table::table["pi"] = 3.1415926535897932385;
    table::table["e"] = 2.7182818284590452354;

    try
    {
        driver::calculate();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to calculate expression: " << e.what() << '\n';
        return 1;
    }

    return error::no_of_errors;
}