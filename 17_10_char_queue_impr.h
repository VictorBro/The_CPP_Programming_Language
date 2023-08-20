#ifndef INCLUDE_GUARDS_17_10_IMPR_H
#define INCLUDE_GUARDS_17_10_IMPR_H

class Char_queue_impr
{
  struct Cell
  {
    Cell *next_;
    char *queue_;
    unsigned head_, tail_;
  };
  static unsigned const default_capacity;
  unsigned const capacity_;
  Cell out_cell_;
  Cell *in_;

public:
  Char_queue_impr(unsigned capacity = default_capacity)
      : in_{&out_cell_}, capacity_{capacity}
  {
    out_cell_.next_ = nullptr;
    out_cell_.queue_ = nullptr;
  }
  ~Char_queue_impr();
  bool empty() const { return out_cell_.next_ == nullptr; }
  bool cell_empty(const Cell &cell) { return cell.head_ == cell.tail_; }
  char dequeue();
  void enqueue(char);
  bool cell_full(const Cell &cell) const { return cell.head_ == (cell.tail_ + 1) % capacity_; }
  static bool const fixed_capacity;
};

#endif