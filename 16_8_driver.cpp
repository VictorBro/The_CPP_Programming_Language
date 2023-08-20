#include "16_8_driver.h"
#include "16_8_lexer.h"
#include "16_8_parser.h"
#include "16_8_table.h"
#include "16_8_error.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

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

int driver::start_calculator(int argc, char *argv[])
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