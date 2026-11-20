#include "ft_printf.h"

int             getnum_untill_not(const char **c)
{
    int ans;

    ans = 0;
    while (!(**c >= '0' && **c <= '9') && **c != '\0' &&
            !(**c == 'c' || **c == 's' || **c == 'p' ||
            **c == 'd' || **c == 'i' || **c == 'u' ||
            **c == 'x' || **c == 'X' || **c == '%'))
        (*c)++;
    while (**c >= '0' && **c <= '9' && **c != '\0')
    {
        ans *= 10;
        ans += ((**c) - '0');
        (*c)++;
    }
    return ans;
}

void            reset_t_format(t_format *t)
{
    (*t).precision = -1;  // ค่าหลังจุด .
    (*t).width = 0;      // ความกว้างขั้นต่ำ (Width)
    (*t).minus = 0;      // แฟล็ก '-' (จัดชิดซ้าย)
    (*t).zero = 0;       // แฟล็ก '0' (เติมเลขศูนย์)
    (*t).hash = 0;       // แฟล็ก '#' (ใช้กับเลขฐาน 16)
    (*t).space = 0;      // แฟล็ก ' ' (เว้นวรรคเลขบวก)
    (*t).plus = 0;       // แฟล็ก '+' (แสดงเครื่องหมายบวก)
    (*t).type = 0;       // ชนิดข้อมูล (c, s, p, d, i, u, x, X, %)
}

int             set_all_bonus_2(const char **c, t_format *data_struct)
{
    if (**c == '0')
        (*data_struct).zero = 1;
    else if (**c == '-')
        (*data_struct).minus = 1;
    else if (**c == '#')
        (*data_struct).hash = 1;
    else if (**c == ' ')
        (*data_struct).space = 1;
    else if (**c == '+')
        (*data_struct).plus = 1;
    if (**c == '0' || **c == '-' || **c == '#' || 
        **c == ' ' || **c == '+')
        return 1;
    else
        return 0;
}

void            set_all_bonus(const char **c, t_format *data_all)
{
    reset_t_format(data_all);
    (*c)++;
    while (**c != '\0')
    {
        if (set_all_bonus_2(c, data_all) == 1)
            (*c)++;
        else if (**c == 'c' || **c == 's' || **c == 'p' || **c == 'd' ||
            **c == 'i' || **c == 'u' || **c == 'x' || **c == 'X' ||
            **c == '%')
        {
            (*data_all).type = **c;
            break;
        }
        else if (**c == '.')
            (*data_all).precision = getnum_untill_not(c);
        else if ((*((*c)) >= '1' && *((*c)) <= '9'))
            (*data_all).width = getnum_untill_not(c);
        else
            (*c)++;
            
    }
}

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

int            print_s(char *c, t_format *data_all)
{
    int width_data;
    int len;

    if (c == NULL)
        if ((*data_all).precision == -1 || (*data_all).precision >= 6)
            c = "(null)";
        else
            c = "";
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

int	calculatelen(int len, int width_data, int has_sign, int precision_data)
{
	int	total_len;

	(void)len;
	total_len = precision_data + has_sign;
	if (width_data > total_len)
		return (width_data);
	return (total_len);
}

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

void print_0X(unsigned long p, t_format *data_all)
{
    if (p != 0 && (*data_all).hash == 1 && (*data_all).type == 'x')
        write(1, "0x", 2);
    else if (p != 0 && (*data_all).hash == 1 && (*data_all).type == 'X')
        write(1, "0X", 2);
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

int            print_something(t_format *data_all, va_list *arg_ptr)
{
    if ((*data_all).type == 'c')
        return print_c((char)va_arg(*arg_ptr, int), data_all);
    else if ((*data_all).type == 's')
        return print_s(va_arg(*arg_ptr, char *), data_all);
    else if ((*data_all).type == 'p')
        return print_p((unsigned long)(va_arg(*arg_ptr, void *)), data_all);
    else if ((*data_all).type == 'd' || (*data_all).type == 'i')
        return print_d(va_arg(*arg_ptr, int), data_all);
    else if ((*data_all).type == 'u')
        return print_u(va_arg(*arg_ptr, unsigned int), data_all);
    else if ((*data_all).type == 'x')
        return print_x(va_arg(*arg_ptr, unsigned int), data_all);
    else if ((*data_all).type == 'X')
        return print_x(va_arg(*arg_ptr, unsigned int), data_all);
    else if ((*data_all).type == '%')
        return print_c('%', data_all);
    return (0);
}

int ft_printf(const char *c, ...)
{
    va_list     arg_ptr;
    t_format    data_all;
    int         len;

    va_start(arg_ptr, c);
    len = 0;
    while(*c != '\0')
    {
        if (*c == '%' && *(c + 1) != '\0')
        {
            set_all_bonus(&c, &data_all);
            len += print_something(&data_all, &arg_ptr);
        } 
        else
        {
            len += 1;
            write(1,c,1);
        }
        if (*c != '\0')
            c++;
    }
    va_end(arg_ptr);
    return len;
}

void main(void)
{
    int ret_sys;
    int ret_ft;

    printf("=== Test 1: Hash + Width (จัดหน้ากว้าง 10) ===\n");
    ret_sys = printf("Sys : [%#10x]\n", 42);
    ret_ft  = ft_printf("Mine: [%#10x]\n", 42);
    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

    printf("=== Test 2: Hash + Zero Padding (เติม 0 ให้เต็ม 10) ===\n");
    ret_sys = printf("Sys : [%#010x]\n", 42);
    ret_ft  = ft_printf("Mine: [%#010x]\n", 42);
    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

    printf("=== Test 3: Hash + Precision (ทศนิยม 5 ตำแหน่ง) ===\n");
    ret_sys = printf("Sys : [%#.5x]\n", 42);
    ret_ft  = ft_printf("Mine: [%#.5x]\n", 42);
    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

    printf("=== Test 4: Hash + Value 0 (เลข 0 ต้องไม่มี 0x) ===\n");
    ret_sys = printf("Sys : [%#10x]\n", 0);
    ret_ft  = ft_printf("Mine: [%#10x]\n", 0);
    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);


    ret_sys = printf("[%#.5x]\n", 42);
    ret_ft  = ft_printf("[%#.5x]\n", 42);
    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

    ret_sys = printf("[%.0x]\n", 0);
    ret_ft  = ft_printf("[%.0x]\n", 0);
    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

    ret_sys = printf("[%#x]\n", 42);
    ret_ft  = ft_printf("[%#x]\n", 42);
    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

    printf("[%#.3x]\n", 42);
    ft_printf("[%#.3x]\n\n", 42);

    printf("%.10p\n", 42);
    ft_printf("%.10p\n", 42);

}