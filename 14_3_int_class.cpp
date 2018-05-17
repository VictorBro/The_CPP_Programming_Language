#include <iostream>
#include <limits>
#include <climits>

using namespace std;

class Int
{
  private:
    long long i;

    void check (long long d) const;

  public:
    Int() { i = 0; }
    Int (long long d) { check(d); i = d; }

    Int(const Int &) = delete;
    Int &operator=(const Int &) = delete;

    int get() const {
        return i;
    }
};

void Int::check (long long d) const
{
    if (d > numeric_limits<int>::max()) {
        throw overflow_error{"Int overflow"};
    } else if (d < numeric_limits<int>::min()) {
        throw underflow_error{"Int underflow"};
    }
}

int main()
{
    try
    {
        //Int myint (2147483649);
        Int myint (-2147483649);
        cout << "myint = " << myint.get() << "\n";
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << '\n';
    }
}