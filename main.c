#include <stdarg.h>
#include <unistd.h>

#include <stdio.h>

// void    int_to_str(int  i,int lenght)
// {
//     char            c;

//     while (lenght > 0)
//     {
//         c = ((i / t) % 10) + '0';
//         t /= 10;
//         write(1,&c,1);
//     }
// }

// int             len_of_int(int i)
// {
//     unsigned int    len;
//     unsigned int    t;

//     len = 11;
//     t = 1000000000;
//     if (i >= 0)
//         len--;
//     else
//         i *= -1;
//     while(i / t == 0)
//     {
//         len--;
//         t /= 10;
//     }
//     return len;
// }

// short           find_flag(const char *c,char key,char stop)
// {
//     while (*c != stop)
//     {
//         if (*c == key)
//             return 1;
//         c++;
//     }
//     return 0;
// }

// unsigned int    len_of_string(const char *c)
// {
//     unsigned int    ans;

//     ans = 0;
//     while(*c != '\0')
//     {
//         ans++;
//         c++;
//     }
//     return ans;
// }

// void            print_string_versatile(const char *c, unsigned int l, char p)
// {
//     if (p == 0)
//         while(l > 0 && *c != '\0')
//         {
//             l--;
//             write(1, c++, 1);
//         }
//     else
//         while(l > 0)
//         {
//             l--;
//             write(1, &p, 1);
//         }
// }

// void            print_s(const char *c, int Precision, int Padding0, int Padding_)
// {
//     unsigned int    len;

//     len = len_of_string(c);
//     if (Precision != -1)
//         len = Precision;
//     if (Padding0 != -1 && Padding_ == -1)
//         print_string_versatile(c, Padding0, ' ');
//     if (Precision != -1)
//         print_string_versatile(c, len, 0);
//     if (Padding_ != -1)
//         print_string_versatile(c, Padding0, '0');
// }

int             getnum_untill_not(const char **c)
{
    int ans;

    ans = 0;
    (*c)++;
    while(**c >= '0' && **c <= '9')
    {
        ans *= 10;
        ans += ((**c) - '0');
        (*c)++;
    }
    return ans;
}

char            set_all_bonus(const char **c, int *Precision, int *Padding0, int *Padding_)
{
    while (**c != '\0')
    {
        if (**c == 'c' || **c == 's' || **c == 'p' || **c == 'd' ||
            **c == 'i' || **c == 'u' || **c == 'x' || **c == 'X' ||
            **c == '%')
            return (**c);
        else if (**c == '.')
            (*Precision) = getnum_untill_not(c);
        else if (**c == '-' && (*Precision) == -1)
            (*Padding0) = getnum_untill_not(c);
        else if (**c == '-' && (*Precision) == -1 && (*Padding0) == -1)
            (*Padding_) = getnum_untill_not(c);
        else
            (*c)++;
    }
    return 0;
}

void            print_something(const char **c)
{
    (*c)++;
    int     Precision;
    int     Padding0;
    int     Padding_;
    char    type;

    Precision = -1;
    Padding0 = -1;
    Padding_ = -1;
    type = set_all_bonus(c, &Precision, &Padding0, &Padding_);
    printf("  Precision %d Padding0 %d Padding_ %d type %c  ",Precision,Padding0,Padding_,type);
    // if (type == 'c')
    // else if (type == 's')
    // else if (type == 'p')
    // else if (type == 'd')
    // else if (type == 'i')
    // else if (type == 'u')
    // else if (type == 'x')
    // else if (type == 'X')
    // else if (type == '%')
}

int ft_printf(const char *c, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, c);
    void *argv;

    while(*c != '\0')
    {
        if (*c == '%')
        {
            argv = va_arg(arg_ptr, void *);
            print_something(&c);
        } 
        else
            write(1,c++,1);
    }
    va_end(arg_ptr);
}


void main(void)
{
    ft_printf("bhyjyde%syng","   ");
    //printf("[%0-.5d]", 42);
    //printf("%zu",getnum("8545620ddddd"));
    //ft_printf("fghrfh%sbtgf"," hello ");
}