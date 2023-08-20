#ifndef INCLUDE_GUARDS_17_4_H
#define INCLUDE_GUARDS_17_4_H

#include <cstddef>
#include <iostream>

class Histogram
{
    ptrdiff_t const minval_, maxval_;
    size_t const gap_;
    size_t *const bin_;
    size_t n_too_small_, n_too_large_;

  public:
    Histogram(ptrdiff_t minval, size_t gap, size_t n_bins);
    ~Histogram() { delete[] bin_; }
    void record(ptrdiff_t);
    void output_to(std::ostream &);
};

#endif