#include "ft_printf.h"


void            print_str(char *c, int precision)
{
    while (*c != '\0' && precision > 0)
    {
        write(1, c, 1);
        c++;
        precision--;
    }
}

void            print_char(char c, int len)
{
    while (len > 0)
    {
        write(1, &c, 1);
        len -= 1;
    }
}


void            print_num(long p, int len, int precision)
{
    long t;
    char c;

    t = 1;
    if (precision == 0 && p == 0)
        return;
    while (len > 0)
    {
        t *= 10;
        len--;
    }
    t /= 10;
    while (t > 0)
    {
        c = ((p / t) % 10) + '0';
        t /= 10;
        write(1, &c, 1);
    }
}

void            print_plus_space(long *p, t_format *data_all)
{
    if ((*data_all).plus == 1 && *p >= 0)
    {
        write(1, "+", 1);
    }
    else if ((*data_all).space == 1 && *p >= 0)
    {
        write(1, " ", 1);
    }
    if (*p < 0)
    {
        write(1, "-", 1);
        *p *= -1;
    }
}