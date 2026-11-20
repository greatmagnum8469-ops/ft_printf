#include "ft_printf.h"


void print_0X(unsigned long p, t_format *data_all)
{
    if (p != 0 && (*data_all).hash == 1 && (*data_all).type == 'x')
        write(1, "0x", 2);
    else if (p != 0 && (*data_all).hash == 1 && (*data_all).type == 'X')
        write(1, "0X", 2);
}


int     recure_print_hex(unsigned long p, t_format *data_all)
{
    int len;

    if (p == 0 && (*data_all).precision == 0)
        return (0);
    if (p == 0)
    {
        write(1, "0", 1);
        return (1);
    }
    len = 0;
    if (p >= 16)
        len += recure_print_hex(p/16, data_all);
    if ((*data_all).type == 'x')
        write(1, ("0123456789abcdef")+((p) % 16), 1);
    else if ((*data_all).type == 'X')
        write(1, ("0123456789ABCDEF")+((p) % 16), 1);
    return len + 1;
}

int    print_x(unsigned int p, t_format *data_all)
{
    int len;
    int width_data;
    int precision_data;
    int len_hash;

    width_data = (*data_all).width;
    precision_data = (*data_all).precision;
    len = count_len_x(p, data_all);
    len_hash = 0;
    if ((*data_all).hash == 1 && p != 0)
        len_hash = 2;
    if ((precision_data < len || precision_data == -1))
        precision_data = len;
    if ((*data_all).minus == 0 && ((*data_all).zero == 0 || (*data_all).precision != -1))
        print_char(' ', width_data - precision_data - len_hash);
    print_0X(p, data_all);
    if (precision_data > len)
        print_char('0', precision_data - len);
    else if ((*data_all).zero == 1 && (*data_all).minus == 0 && (*data_all).precision == -1)
        print_char('0', width_data - precision_data - len_hash);
    recure_print_hex(p, data_all);
    if ((*data_all).minus == 1)
        print_char(' ', width_data - precision_data - len_hash);
    return (calculatelen(len,width_data,len_hash,precision_data));
}