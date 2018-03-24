#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

const int N = 100000;
//using CFT = int(const void *, const void *);

int compare(const void *a, const void *b)
{
    return (*static_cast<const int*>(a) - *static_cast<const int*>(b));
}

int main()
{
    int arr1[N], arr2[N];
    clock_t begin, end;
    double time_spent;

    srand(time(nullptr));
    for (int i = 0; i < N; ++i) {
        arr2[i] = arr1[i] = rand() % (N / 10);
    }

    begin = clock();
    qsort(arr1, N, sizeof(int), compare);
    end = clock();
    time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken by qsort = " << time_spent << "\n";

    begin = clock();
    sort(arr2,arr2 + N);
    end = clock();
    time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken by sort = " << time_spent << "\n";
}