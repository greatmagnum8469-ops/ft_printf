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