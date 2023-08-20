#include "17_10_char_queue_list.h"
#include <string>
#include <stdexcept>

bool const Char_queue_list::fixed_capacity = false;

Char_queue_list::~Char_queue_list()
{
    for (Cell *p = out_cell_.next_; p;)
    {
        Cell *victim = p;
        p = p->next_;
        delete victim;
    }
}

char Char_queue_list::dequeue()
{
    if (!empty())
    {
        Cell *victim = out_cell_.next_;
        char c = victim->c_;
        out_cell_.next_ = victim->next_;
        delete victim;
        return c;
    }
    else
    {
        throw std::underflow_error{std::string{"queue"}};
    }
}

void Char_queue_list::enqueue(char c)
{
    in_->next_ = new (std::nothrow) Cell;
    if (!in_->next_)
    {
        throw std::overflow_error{std::string{"queue"}};
    }
    in_ = in_->next_;
    in_->next_ = nullptr;
    in_->c_ = c;
}