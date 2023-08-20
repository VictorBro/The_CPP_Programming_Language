#include "17_7_intset.h"

void Intset::insert(int number)
{
    for (int x : int_set)
    {
        if (x == number)
        {
            return;
        }
    }
    int_set.push_back(number);
}

void Intset::print_to(std::ostream &output)
{
    for (int x : int_set)
    {
        output << x << " ";
    }
    output << '\n';
}

Intset set_union(const Intset &set1, const Intset &set2)
{
    Intset res{};

    for (int x : set1.get_int_set())
    {
        res.insert(x);
    }
    for (int x : set2.get_int_set())
    {
        res.insert(x);
    }
    return res;
}

Intset set_intersection(const Intset &set1, const Intset &set2)
{
    Intset res{};

    for (int x : set1.get_int_set())
    {
        for (int y : set2.get_int_set())
        {
            if (x == y)
            {
                res.insert(x);
            }
        }
    }
    return res;
}

Intset set_symmetric_diff(const Intset &set1, const Intset &set2)
{
    Intset res{};
    bool found = false;

    for (int x : set1.get_int_set())
    {
        for (int y : set2.get_int_set())
        {
            if (x == y)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            res.insert(x);
        }
        found = false;
    }

    for (int x : set2.get_int_set())
    {
        for (int y : set1.get_int_set())
        {
            if (x == y)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            res.insert(x);
        }
        found = false;
    }
    
    return res;
}