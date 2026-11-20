#include "ft_printf.h"



int    print_d(int num, t_format *data_all)
{
    int len;
    int width_data;
    int has_sign;
    int precision_data;
    long p;

    p = (long) num;
    has_sign = ((*data_all).plus == 1 || (*data_all).space == 1 || p < 0);
    width_data = (*data_all).width;
    precision_data = (*data_all).precision;
    len = count_len_d(p, (*data_all).precision);
    if ((precision_data < len || precision_data == -1))
        precision_data = len;
    if ((*data_all).minus == 0 && ((*data_all).zero == 0 || (*data_all).precision != -1))
        print_char(' ', width_data - precision_data - has_sign);
    print_plus_space(&p, data_all);
    if (precision_data > len)
        print_char('0', precision_data - len);
    else if ((*data_all).zero == 1 && (*data_all).minus == 0 && (*data_all).precision == -1)
        print_char('0', width_data - precision_data - has_sign);
    print_num(p, len, (*data_all).precision);
    if ((*data_all).minus == 1)
        print_char(' ', width_data - precision_data - has_sign);
    return (calculatelen(len,width_data,has_sign,precision_data));
}

int    print_u(unsigned int num, t_format *data_all)
{
    int len;
    int width_data;
    int precision_data;
    long p;

    p = (long) num;
    width_data = (*data_all).width;
    precision_data = (*data_all).precision;
    len = count_len_d(p, (*data_all).precision);
    if ((precision_data < len || precision_data == -1))
        precision_data = len;
    if ((*data_all).minus == 0 && ((*data_all).zero == 0 || (*data_all).precision != -1))
        print_char(' ', width_data - precision_data);
    if (precision_data > len)
        print_char('0', precision_data - len);
    else if ((*data_all).zero == 1 && (*data_all).minus == 0 && (*data_all).precision == -1)
        print_char('0', width_data - precision_data);
    print_num(p, len, (*data_all).precision);
    if ((*data_all).minus == 1)
        print_char(' ', width_data - precision_data );
    return (calculatelen(len,width_data,0,precision_data));
}