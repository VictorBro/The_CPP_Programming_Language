#include "17_4_histogram.h"
#include <iostream>
#include <cassert>

Histogram::Histogram(ptrdiff_t minval, size_t gap, size_t n_bins)
    : minval_{minval}, maxval_{minval + static_cast<ptrdiff_t>(n_bins * gap) - 1}, gap_{gap},
      bin_{new size_t[n_bins]{}}, n_too_small_{0}, n_too_large_{0}
{
    assert(gap != 0 && n_bins != 0);
}

void Histogram::record(ptrdiff_t datapoint)
{
    if (datapoint < minval_)
    {
        ++n_too_small_;
    }
    else if (datapoint > maxval_)
    {
        ++n_too_large_;
    }
    else
    {
        ++bin_[(datapoint - minval_) / gap_];
    }
}

void Histogram::output_to(std::ostream &output)
{
    output << "< " << minval_ << ": " << n_too_small_ << '\n';
    for (ptrdiff_t left = minval_; left < maxval_; left += gap_)
    {
        output << left << ".." << left + gap_ - 1 << ": "
               << bin_[(left - minval_) / gap_] << '\n';
    }
    output << "> " << maxval_ << ": " << n_too_large_ << '\n';
}
