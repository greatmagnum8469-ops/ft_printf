

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h> // สำหรับ malloc/free (ถ้ามีใช้ในอนาคต)
# include <stdio.h>
# include <limits.h> // สำหรับ INT_MAX, INT_MIN
/* 
** โครงสร้างสำหรับเก็บสถานะของ Format Specifiers ทั้งหมด 
** (ทั้งแบบปกติและส่วนโบนัส เช่น แฟล็ก, ความกว้าง, และความละเอียด)
*/
typedef struct s_format
{
    int     precision;  // ค่าหลังจุด .
    int     width;      // ความกว้างขั้นต่ำ (Width)
    int     minus;      // แฟล็ก '-' (จัดชิดซ้าย)
    int     zero;       // แฟล็ก '0' (เติมเลขศูนย์)
    int     hash;       // แฟล็ก '#' (ใช้กับเลขฐาน 16)
    int     space;      // แฟล็ก ' ' (เว้นวรรคเลขบวก)
    int     plus;       // แฟล็ก '+' (แสดงเครื่องหมายบวก)
    char    type;       // ชนิดข้อมูล (c, s, p, d, i, u, x, X, %)
}               t_format;

/* 
** Function Prototypes 
*/
int     ft_printf(const char *format, ...);

// ตัวอย่างฟังก์ชันเสริมที่คุณอาจจะแยกไปไว้ในไฟล์อื่น
// void    parse_format(const char **format, t_format *fmt);
// int     ft_print_format(t_format *fmt, va_list args);

#endif