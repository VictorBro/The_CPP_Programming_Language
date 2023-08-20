#ifndef INCLUDE_GUARDS_17_2_H
#define INCLUDE_GUARDS_17_2_H

#include <string>
#include <map>

namespace my_chrono
{

enum class Month
{
    jan = 1,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    oct,
    nov,
    dec
};

extern std::map<Month, std::string> month_to_str;

class Date
{
    int days_from_1Jan1970;
    mutable bool cache_valid;
    mutable std::string cache;

    void compute_cache_value() const;

  public:
    class Bad_date
    {
    };
    class Bad_argument
    {
    };
    class Bad_month
    {
    };

    explicit Date(int = 1, Month = Month::jan, int = 1970);
    int day() const;
    Month month() const;
    int year() const;
    std::string string_rep() const;
    Date &add_year(int);
    Date &add_month(int);
    Date &add_day(int);
};

void A1Jan1970_to_DMY(int, int &, Month &, int &);
void DMY_to_A1Jan1970(int, Month, int, int &);
bool is_leapyear(int);
int get_num_of_days_in_month(Month, int);
bool is_valid_date(int, Month, int);

} // namespace my_chrono

#endif