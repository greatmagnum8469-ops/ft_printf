# ชื่อของไฟล์ Library ที่โจทย์บังคับ
NAME	= libftprintf.a

# ตั้งค่า Compiler และ Flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

# รายชื่อไฟล์ Source Code ตามที่คุณมี (ไม่รวม main.c)
SRCS	= all_print.c \
		  count_len.c \
		  print_c_s.c \
		  print_d_i.c \
		  print_p.c \
		  print_x.c \
		  set_format.c \
		  centor.c

# แปลงนามสกุล .c เป็น .o
OBJS	= $(SRCS:.c=.o)

# กฎหลัก
all: $(NAME)

# กฎการสร้าง libftprintf.a
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# กฎการคอมไพล์ไฟล์ .c เป็น .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ลบไฟล์ .o
clean:
	$(RM) $(OBJS)

# ลบไฟล์ .o และไฟล์ .a
fclean: clean
	$(RM) $(NAME)

# ล้างทั้งหมดแล้วคอมไพล์ใหม่
re: fclean all

.PHONY: all clean fclean re