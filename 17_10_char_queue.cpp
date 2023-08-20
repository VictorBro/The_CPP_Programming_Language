#include "17_10_char_queue.h"
#include <string>
#include <stdexcept>

bool const Char_queue::fixed_capacity = true;
unsigned const Char_queue::default_capacity = 20;    

char Char_queue::dequeue()
{
    if (!empty())
    {
        char c = queue_[head_];
        head_ = (head_ + 1) % capacity_;
        return c;
    }
    else
    {
        throw std::underflow_error{std::string{"queue"}};
    }
}

void Char_queue::enqueue(char c)
{
    if (!full())
    {
        queue_[tail_] = c;
        tail_ = (tail_ + 1) % capacity_;
    }
    else
    {
        throw std::overflow_error{std::string{"queue"}};
    }
}