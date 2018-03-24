#include <iostream>
#include <cstring>

int main(int argc, char* argv[])
{
    char ch = '\0';
    size_t key_size = 0;
    char* key = nullptr;
    size_t i = 0;

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <key_string>\n";
        return 1;
    }

    key = argv[1];
    key_size = strlen(key);

    while (std::cin.get(ch)) {
        char cypher = ch ^ key[i];
        std::cout.put(cypher);
        i = (i + 1) % key_size; 
    }
    std::cout << "\n";
}