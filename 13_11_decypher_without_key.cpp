/*
 * In this program the assumption is that key 
 * consists of lowercase characters only, and
 * the key size is at most 5 characters.
 */
#include <iostream>
#include <cstring>

const int buf_size = 256;
const int max_key_size = 5;
const int key_alphabet_range = 26;

void decypher(char* cypher, int n)
{
    std::cout << "\n";
    char plain = '\0';
    char matrix[max_key_size][key_alphabet_range] = {0};
    bool is_first_time[max_key_size] = {true, true, true, true, true};

    for (int key_size = 1; key_size <= max_key_size; ++key_size) {
        for (int i = 0; i < n; ++i) {
            char temp[key_alphabet_range] = {0};
            for (int ascii_index = 0; ascii_index < key_alphabet_range; ++ascii_index) {
                plain = cypher[i] ^ ('a' + ascii_index);
                if (isalpha(plain)) {
                    temp[ascii_index] = 'a' + ascii_index;
                }
            }
            if (is_first_time[i % key_size]) {
                for (int j = 0; j < key_alphabet_range; ++j) {
                    matrix[i % key_size][j] = temp[j];
                }
                is_first_time[i % key_size] = false;
            } else {
                for (int j = 0; j < key_alphabet_range; ++j) {
                    matrix[i % key_size][j] &= temp[j];
                }
            }
        }
        std::cout << "key size " << key_size << ":\n";
        for (int i = 0; i < max_key_size; ++i) {
            std::cout << i << ": ";
            for (int j = 0; j < key_alphabet_range; ++j) {
                std::cout.put(matrix[i][j]);
                std::cout << " ";
            }
            std::cout << "\n";
        }
        memset(matrix, 0, sizeof(matrix[0][0]) * key_alphabet_range * max_key_size);
        for (int i = 0; i < max_key_size; ++i) {
            is_first_time[i] = true;
        }
    }
}

int main(int argc, char* argv[])
{
    char ch = '\0';
    size_t key_size = 0;
    char* key = nullptr;
    size_t i = 0;
    char cypher[buf_size] = {0};

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <key_string>\n";
        return 1;
    }

    key = argv[1];
    key_size = strlen(key);
    while (std::cin.get(ch) && ch != '#' && i < buf_size) {
        cypher[i] = ch ^ key[i % key_size];
        std::cout.put(cypher[i]);
        ++i; 
    }
    cypher[i] = '\0';
    std::cout << "\n";

    decypher(cypher, i);
}