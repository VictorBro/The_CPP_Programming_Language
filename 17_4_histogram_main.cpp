#include "17_4_histogram.h"

using namespace std;

int main()
{
    Histogram my_hist{1, 2, 5};
    for (int i = 0; i < 5; i++)
    {
        my_hist.record(0);
    }
    for (int i = 0; i < 10; i++)
    {
        my_hist.record(i);
    }
    for (int i = 5; i < 10; i++)
    {
        my_hist.record(i);
    }

    for (int i = 10; i < 13; i++)
    {
        my_hist.record(i);
    }
    my_hist.output_to(cout);
}
