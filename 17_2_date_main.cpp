#include "17_2_date.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    try
    {
        my_chrono::Date my_date{31, my_chrono::Month::dec, 1972};
        cout << my_date.string_rep() << endl;
        cout << "kuku: " << my_date.day() << " " << static_cast<int>(my_date.month()) << " " << my_date.year() << endl;
        my_date.add_year(1);
        cout << my_date.string_rep() << endl;
        my_date.add_month(11);
        cout << my_date.string_rep() << endl;
        my_date.add_day(366);
        cout << my_date.string_rep() << endl;
    }
    catch (const my_chrono::Date::Bad_date &e)
    {
        cout << "Bad date is provided\n";
    }
    catch (const my_chrono::Date::Bad_argument &e)
    {
        cout << "Bad argument is provided\n";
    }
    catch (const my_chrono::Date::Bad_month &e)
    {
        cout << "Bad month\n";
    }
}
