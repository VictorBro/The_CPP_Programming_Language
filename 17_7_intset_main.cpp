#include "17_7_intset.h"

using namespace std;

int main()
{
    Intset my_set{};
    for (int i = 1; i <= 10; ++i)
    {
        my_set.insert(i);
    }

    for (int i = 1; i <= 10; i += 2)
    {
        my_set.insert(i);
    }
    my_set.print_to(cout);

    Intset my_set2{};
    for (int i = 9; i <= 12; ++i)
    {
        my_set2.insert(i);
    }

    Intset union_set = set_union(my_set, my_set2);
    union_set.print_to(cout);

    Intset inter_set = set_intersection(my_set, my_set2);
    inter_set.print_to(cout);

    Intset symm_diff = set_symmetric_diff(my_set, my_set2);
    symm_diff.print_to(cout);
}