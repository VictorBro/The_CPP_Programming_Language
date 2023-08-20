#include "17_2_date.h"
#include <iostream>
#include <ctime>

using namespace std;

std::map<my_chrono::Month, std::string> my_chrono::month_to_str = {{Month::jan, "Jan"},
                                                                   {Month::feb, "Feb"},
                                                                   {Month::mar, "Mar"},
                                                                   {Month::apr, "Apr"},
                                                                   {Month::may, "May"},
                                                                   {Month::jun, "Jun"},
                                                                   {Month::jul, "Jul"},
                                                                   {Month::aug, "Aug"},
                                                                   {Month::sep, "Sep"},
                                                                   {Month::oct, "Oct"},
                                                                   {Month::nov, "Nov"},
                                                                   {Month::dec, "Dec"}};

my_chrono::Date::Date(int dd, Month mm, int yy)
{
    if (!is_valid_date(dd, mm, yy))
        throw Bad_date{};
    DMY_to_A1Jan1970(dd, mm, yy, this->days_from_1Jan1970);
    cache_valid = false;
}

int my_chrono::Date::day() const
{
    int day;
    Month month;
    int year;

    A1Jan1970_to_DMY(this->days_from_1Jan1970, day, month, year);
    return day;
}

my_chrono::Month my_chrono::Date::month() const
{
    int day;
    Month month;
    int year;

    A1Jan1970_to_DMY(this->days_from_1Jan1970, day, month, year);
    return month;
}

int my_chrono::Date::year() const
{
    int day;
    Month month;
    int year;

    A1Jan1970_to_DMY(this->days_from_1Jan1970, day, month, year);
    return year;
}

bool my_chrono::is_leapyear(int y)
{
    return !(y % 4) && ((y % 100) || !(y % 400));
}

int my_chrono::get_num_of_days_in_month(Month m, int y)
{
    int ndays;

    switch (m)
    {
    case Month::feb:
        ndays = 28 + is_leapyear(y);
        break;
    case Month::apr:
    case Month::jun:
    case Month::sep:
    case Month::nov:
        ndays = 30;
        break;
    case Month::jan:
    case Month::mar:
    case Month::may:
    case Month::jul:
    case Month::aug:
    case Month::oct:
    case Month::dec:
        ndays = 31;
        break;
    default:
        return 0;
    }

    return ndays;
}

bool my_chrono::is_valid_date(int d, Month m, int y)
{
    int ndays;

    if (y < 1970)
        return false;

    ndays = get_num_of_days_in_month(m, y);

    if (ndays == 0)
    {
        return false;
    }
    else
    {
        return 1 <= d && d <= ndays;
    }
}

void my_chrono::A1Jan1970_to_DMY(int days, int &day, Month &month, int &year)
{
    tm temp;
    temp.tm_sec = 0;
    temp.tm_min = 0;
    temp.tm_hour = 12;
    temp.tm_mday = 1 + days;
    temp.tm_mon = 0;
    temp.tm_year = 70;
    mktime(&temp);

    day = temp.tm_mday;
    month = static_cast<Month>(temp.tm_mon + 1);
    year = 1900 + temp.tm_year;
}

void my_chrono::DMY_to_A1Jan1970(int day, Month month, int year, int &days)
{
    tm temp;
    temp.tm_sec = 0;
    temp.tm_min = 0;
    temp.tm_hour = 12;
    temp.tm_mday = day;
    temp.tm_mon = static_cast<int>(month) - 1;
    temp.tm_year = year - 1900;
    time_t seconds = mktime(&temp);

    days = (seconds / 86400);
}

void my_chrono::Date::compute_cache_value() const
{
    int day;
    Month month;
    int year;

    A1Jan1970_to_DMY(this->days_from_1Jan1970, day, month, year);
    cache = to_string(day) + " " + month_to_str[month] + " " + to_string(year);
}

string my_chrono::Date::string_rep() const
{
    if (!cache_valid)
    {
        compute_cache_value();
        cache_valid = true;
    }
    return cache;
}

my_chrono::Date &my_chrono::Date::add_year(int n)
{
    int day;
    Month month;
    int year;

    if (n == 0)
        return *this;

    if (n < 0)
        throw Bad_argument{};

    A1Jan1970_to_DMY(this->days_from_1Jan1970, day, month, year);
    if (day == 29 && month == Month::feb && !is_leapyear(year + n))
    {
        day = 1;
        month = Month::mar;
    }
    year += n;
    DMY_to_A1Jan1970(day, month, year, this->days_from_1Jan1970);
    cache_valid = false;
    return *this;
}

my_chrono::Date &my_chrono::Date::add_month(int n)
{
    int day;
    Month month;
    int year;

    if (n == 0)
        return *this;

    if (n < 0)
        throw Bad_argument{};

    A1Jan1970_to_DMY(this->days_from_1Jan1970, day, month, year);
    int delta_y = n / 12;
    int mm = static_cast<int>(month) + n % 12;
    if (mm > 12)
    {
        ++delta_y;
        mm -= 12;
    }
    add_year(delta_y);
    A1Jan1970_to_DMY(this->days_from_1Jan1970, day, month, year);
    month = static_cast<Month>(mm);
    if (!is_valid_date(day, month, year))
    {
        int ndays = get_num_of_days_in_month(month, year);
        if (ndays == 0)
            throw Bad_month{};

        if (day > ndays)
            day = ndays;
    }
    DMY_to_A1Jan1970(day, month, year, this->days_from_1Jan1970);
    cache_valid = false;
    return *this;
}

my_chrono::Date &my_chrono::Date::add_day(int n)
{
    int day;
    Month month;
    int year;

    if (n == 0)
        return *this;

    if (n < 0)
        throw Bad_argument{};
    
    this->days_from_1Jan1970 += n;
    A1Jan1970_to_DMY(this->days_from_1Jan1970, day, month, year);
    DMY_to_A1Jan1970(day, month, year, this->days_from_1Jan1970);
    cache_valid = false;
    return *this;
}