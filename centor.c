#include "ft_printf.h"

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

//void main(void)
//{
//    int ret_sys;
//    int ret_ft;

//    printf("=== Test 1: Hash + Width (จัดหน้ากว้าง 10) ===\n");
//    ret_sys = printf("Sys : [%#10x]\n", 42);
//    ret_ft  = ft_printf("Mine: [%#10x]\n", 42);
//    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

//    printf("=== Test 2: Hash + Zero Padding (เติม 0 ให้เต็ม 10) ===\n");
//    ret_sys = printf("Sys : [%#010x]\n", 42);
//    ret_ft  = ft_printf("Mine: [%#010x]\n", 42);
//    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

//    printf("=== Test 3: Hash + Precision (ทศนิยม 5 ตำแหน่ง) ===\n");
//    ret_sys = printf("Sys : [%#.5x]\n", 42);
//    ret_ft  = ft_printf("Mine: [%#.5x]\n", 42);
//    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

//    printf("=== Test 4: Hash + Value 0 (เลข 0 ต้องไม่มี 0x) ===\n");
//    ret_sys = printf("Sys : [%#10x]\n", 0);
//    ret_ft  = ft_printf("Mine: [%#10x]\n", 0);
//    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);


//    ret_sys = printf("[%#.5x]\n", 42);
//    ret_ft  = ft_printf("[%#.5x]\n", 42);
//    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

//    ret_sys = printf("[%.0x]\n", 0);
//    ret_ft  = ft_printf("[%.0x]\n", 0);
//    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

//    ret_sys = printf("[%#x]\n", 42);
//    ret_ft  = ft_printf("[%#x]\n", 42);
//    printf("Sys ret: %d | Mine ret: %d\n\n", ret_sys, ret_ft);

//    printf("[%#.3x]\n", 42);
//    ft_printf("[%#.3x]\n\n", 42);

//    printf("%.10p\n", 42);
//    ft_printf("%.10p\n", 42);

//}