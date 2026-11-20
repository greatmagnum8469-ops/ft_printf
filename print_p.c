#include "ft_printf.h"


int    print_p_recur(unsigned long p)
{
    int len;

    if (p == 0)
    {
        write(1, "0", 1);
        return (1);
    }
    len = 0;
    if (p >= 16)
        len += print_p_recur(p/16);
    write(1, ("0123456789abcdef")+((p) % 16), 1);
    return len + 1;
}

int    print_p(unsigned long p, t_format *data_all)
{
    int len;
    int width_data;

    len = count_len_p(p) + 2;
    if (p == 0)
        len = 5;
    width_data = (*data_all).width;
    if ((*data_all).precision < len)
        (*data_all).precision = len;
    if ((*data_all).minus != 1 && width_data > len)
        print_char(' ', width_data - len);
    if (p == 0)
        write(1, "(nil)", 5);
    else
        write(1, "0x", 2);
    if (((*data_all).precision > len))
        print_char('0', (*data_all).precision - len + 2);
    if (p != 0)
        print_p_recur(p);
    if ((*data_all).minus == 1 && width_data > len)
        print_char(' ', width_data - len);
    if (width_data > len)
        return width_data;
    return len;
}