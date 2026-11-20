#include "ft_printf.h"

int            print_c(char c, t_format *data_all)
{
    int width_data;

    width_data = (*data_all).width;
    if ((*data_all).minus != 1 && width_data != 1)
        while (width_data - 1 > 0)
        {
            write(1, " ", 1);
            width_data -= 1;
        }
    write(1, &c, 1);
    if ((*data_all).minus == 1 && width_data != 1)
        while (width_data - 1 > 0)
        {
            write(1, " ", 1);
            width_data -= 1;
        }
    if ((*data_all).width > 1)
        return (*data_all).width;
    return 1;
}
//////////////////////////////////////////////////////////////////////////
int            print_s(char *c, t_format *data_all)
{
    int width_data;
    int len;

    if (c == NULL)
	{
        if ((*data_all).precision == -1 || (*data_all).precision >= 6)
            c = "(null)";
        else
            c = "";
	}
    len = len_of_str(c);
    width_data = (*data_all).width;
    if ((*data_all).precision > len || (*data_all).precision == -1)
        (*data_all).precision = len;
    if (width_data > (*data_all).precision && (*data_all).minus == 0)
        print_char(' ', width_data - (*data_all).precision);
    print_str(c, (*data_all).precision);
    if (width_data > (*data_all).precision && (*data_all).minus == 1)
        print_char(' ', width_data - (*data_all).precision);
    if (width_data > (*data_all).precision)
        return width_data;
    return (*data_all).precision;
}