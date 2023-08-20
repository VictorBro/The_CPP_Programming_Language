#ifndef INCLUDE_GUARDS_17_10_H
#define INCLUDE_GUARDS_17_10_H

class Char_queue
{
  static unsigned const default_capacity;
  char *queue_;
  unsigned head_, tail_;
  unsigned const capacity_;

public:
  Char_queue(unsigned capacity = default_capacity)
      : queue_{new char[capacity]}, head_{0}, tail_{0}, capacity_{capacity} {}
  ~Char_queue() { delete[] queue_; }
  bool empty() const { return head_ == tail_; }
  char dequeue();
  void enqueue(char);
  bool full() const { return head_ == (tail_ + 1) % capacity_; }
  static bool const fixed_capacity;
};

#endif