#ifndef INCLUDE_GUARDS_17_6_H
#define INCLUDE_GUARDS_17_6_H

#include <iostream>
#include <string>

class Tree
{
  class Tnode
  {
  public:
    std::string word_;
    int count_;
    Tnode *left_;
    Tnode *right_;

    Tnode(std::string word = {}, int count = {}, Tnode *left = nullptr, Tnode *right = nullptr)
        : word_{word}, count_{count}, left_{left}, right_{right}
    {
    }
  };
  Tnode *root_;

  void delete_all(Tnode *);
  Tnode *enter_new_word(Tnode *, std::string);
  void print_tree(Tnode *node, std::ostream &);

public:
  Tree(Tnode *root = nullptr) : root_{root}
  {
  }
  ~Tree() { delete_all(root_); };
  Tnode *insert(std::string);
  void print_to(std::ostream &);
};

#endif