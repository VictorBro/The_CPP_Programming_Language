#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    char ch;

    ifstream inFile(R"(C:\Users\vmb11\OneDrive\Documents\The_CPP_Language\The_CPP_Programming_Language\15_2_calculator.cpp)");
    if (inFile.is_open())
    {
        regex pat(R"(#include\s*<(\w+(.h)?)>)");
        for (string line; getline(inFile, line);)
        {
            smatch matches;
            if (regex_search(line, matches, pat))
            {
                cout << matches[1] << '\n';
            }
        }
        inFile.close();
    }
    else
    {
        cerr << "Error opening file\n";
        exit(1);
    }
}