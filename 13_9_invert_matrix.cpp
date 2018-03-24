#include <iostream>

const int N = 3;
const int M = 5;

void print_matrix(int arr[][M])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void invert_matrix(int arr[][M], int trans[][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            trans[j][i] = arr[i][j];
        }
    }
}

void print_inverted_matrix(int trans[][N]) {
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << trans[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    int arr[N][M] = {
        {10, 11, 12, 13, 14},
        {15, 16, 17, 18, 19},
        {20, 21, 22, 23, 24}};
    
    int trans[M][N] = {0};

    print_matrix(arr);
    invert_matrix(arr, trans);
    std::cout << "---------------------\n";
    print_inverted_matrix(trans);
}