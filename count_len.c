#include "ft_printf.h"



int             len_of_str(char *c)
{
    int count;

    count = 0;
    while (*c != '\0')
    {
        c++;
        count++;
    }
    return count;
}

int    count_len_d(long p, int precision)
{
    int count;
    long t;

    if (p == 0 && precision == 0)
        return (0);
    if (p == 0)
        return (1);
    if (p < 0)
        p *= -1;
    count = 0;
    t = 1;
    while (p / t != 0)
    {
        t *= 10;
        count++;
    }
    return count;
}

int    count_len_p(unsigned long p)
{
    int len;

    if (p == 0)
        return (1);
    len = 0;
    if (p >= 16)
        len += count_len_p(p/16);
    return len + 1;
}


int	calculatelen(int len, int width_data, int has_sign, int precision_data)
{
	int	total_len;

	(void)len;
	total_len = precision_data + has_sign;
	if (width_data > total_len)
		return (width_data);
	return (total_len);
}

int    count_len_x(unsigned int p, t_format *data_all)
{
    int len;

    if (p == 0 && (*data_all).precision == 0)
        return (0);
    if (p == 0)
        return (1);
    len = 0;
    if (p >= 16)
        len += count_len_x(p/16, data_all);
    return len + 1;
}