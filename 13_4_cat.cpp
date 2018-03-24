#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    std::ifstream inFile;

    for (int i = 1; i < argc; ++i) {
        inFile.open(argv[i]);
        if (!inFile.is_open()) {
            std::cerr << "Unable to open file " << argv[i] << "\n";
            continue;
        }
        std::cout << "*************" << argv[i] << "\n";
        for (std::string line; getline(inFile, line);) {
            std::cout << line << "\n";
        }
        inFile.close();
    }
}