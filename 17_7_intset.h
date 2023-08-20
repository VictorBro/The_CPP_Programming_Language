#ifndef INCLUDE_GUARDS_17_7_H
#define INCLUDE_GUARDS_17_7_H

#include <iostream>
#include <vector>

class Intset
{
  std::vector<int> int_set;

public:
  Intset() : int_set{} {}
  void insert(int);
  void print_to(std::ostream &);
  std::vector<int> get_int_set() const { return int_set; }
};

Intset set_union(const Intset &set1, const Intset &set2);
Intset set_intersection(const Intset &set1, const Intset &set2);
Intset set_symmetric_diff(const Intset &set1, const Intset &set2);

#endif