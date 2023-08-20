#include "17_10_char_queue_impr.h"
#include <string>
#include <stdexcept>

bool const Char_queue_impr::fixed_capacity = true;
unsigned const Char_queue_impr::default_capacity = 10;

Char_queue_impr::~Char_queue_impr()
{
    for (Cell *p = out_cell_.next_; p;)
    {
        Cell *victim = p;
        p = p->next_;
        if (p->queue_)
            delete[] p->queue_;
        if (victim)
            delete victim;
    }
}

char Char_queue_impr::dequeue()
{
    if (!empty())
    {
        Cell *victim = out_cell_.next_;
        if (!cell_empty(*victim))
        {
            char *victim_queue = victim->queue_;
            char c = victim_queue[victim->head_];
            victim->head_ = (victim->head_ + 1) % capacity_;
            if (cell_empty(*victim))
            {
                out_cell_.next_ = victim->next_;
                delete[] victim_queue;
                delete victim;
            }
            return c;
        }
    }
    else
    {
        throw std::underflow_error{std::string{"queue"}};
    }
}

void Char_queue_impr::enqueue(char c)
{
    if (in_->queue_ == nullptr || cell_full(*in_))
    {
        in_->next_ = new (std::nothrow) Cell;
        if (!in_->next_)
        {
            throw std::overflow_error{std::string{"Cell"}};
        }
        in_ = in_->next_;
        in_->next_ = nullptr;
        in_->queue_ = new (std::nothrow) char[capacity_];
        if (!in_->queue_)
        {
            throw std::overflow_error{std::string{"queue"}};
        }
        in_->head_ = in_->tail_ = 0;
        in_->queue_[in_->tail_] = c;
        in_->tail_ = (in_->tail_ + 1) % capacity_;
    }
    else
    {
        in_->queue_[in_->tail_] = c;
        in_->tail_ = (in_->tail_ + 1) % capacity_;
    }
}