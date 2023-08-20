#include "16_8_lexer.h"
#include "16_8_error.h"
#include <iostream>

lexer::Token_stream ts{std::cin};

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