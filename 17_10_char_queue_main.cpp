#include "17_10_char_queue.h"
#include "17_10_char_queue_list.h"
#include "17_10_char_queue_impr.h"
#include <iostream>

using namespace std;

int main()
{
    Char_queue my_queue{};
    my_queue.enqueue('H');
    my_queue.enqueue('e');
    my_queue.enqueue('l');
    my_queue.enqueue('l');
    my_queue.enqueue('o');

    try
    {
        for (int i = 0; i < 16; i++)
        {
            my_queue.enqueue('#');
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what() << '\n';
    }

    Char_queue_list my_queue_list{};
    my_queue_list.enqueue('H');
    my_queue_list.enqueue('e');
    my_queue_list.enqueue('l');
    my_queue_list.enqueue('l');
    my_queue_list.enqueue('o');

    try
    {
        for (int i = 0; i < 16; i++)
        {
            my_queue_list.enqueue('#');
        }
        while (!my_queue_list.empty())
        {
            cout << my_queue_list.dequeue();
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what();
    }
    cout << '\n';

    Char_queue_impr my_queue_impr{};
    my_queue_impr.enqueue('H');
    my_queue_impr.enqueue('e');
    my_queue_impr.enqueue('l');
    my_queue_impr.enqueue('l');
    my_queue_impr.enqueue('o');

    try
    {
        for (int i = 0; i < 16; i++)
        {
            my_queue_impr.enqueue('#');
        }
        while (!my_queue_impr.empty())
        {
            cout << my_queue_impr.dequeue();
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what();
    }
}