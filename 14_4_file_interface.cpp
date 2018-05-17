#include <iostream>
#include <stdexcept>
#include <cstdarg>

using namespace std;

FILE *my_fopen(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (fp == nullptr) {
        throw ios_base::failure{"can't open the file"};
    }
    return fp;
}

int my_fclose(FILE *stream)
{
    int rv = fclose(stream);
    if (rv)
        throw ios_base::failure{"can't close the file"};
    return rv;
}

int my_fprintf(FILE *stream, const char *format, ...)
{
    int result;
    va_list args;

    va_start(args, format);
    result = fprintf(stream, format, args);
    va_end(args);

    if (result < 0) {
        throw ios_base::failure{"can't write to file"};
    }

    return result;
}

int main()
{
    try
    {
        //FILE *fp = my_fopen("kyyky.txt", "r");
        FILE *fp = my_fopen("new.txt", "r");
        my_fprintf(fp, "hello");

        my_fclose(fp);
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << "\n";
    }
}