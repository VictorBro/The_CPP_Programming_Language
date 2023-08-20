#ifndef INCLUDE_GUARDS_17_10_LIST_H
#define INCLUDE_GUARDS_17_10_LIST_H

class Char_queue_list
{
  struct Cell
  {
    Cell *next_;
    char c_;
  };
  Cell out_cell_;
  Cell *in_;

public:
  Char_queue_list(unsigned capacity = 0)
      : in_{&out_cell_} { out_cell_.next_ = nullptr; }
  ~Char_queue_list();
  bool empty() const { return out_cell_.next_ == nullptr; }
  char dequeue();
  void enqueue(char);
  static bool const fixed_capacity;
};

#endif