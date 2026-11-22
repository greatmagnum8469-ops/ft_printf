# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/22 13:04:18 by hzheng2           #+#    #+#              #
#    Updated: 2026/11/22 14:55:41 by hzheng2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I. -Ibonus
AR			= ar rcs
RM			= rm -f

SRCS		= all_print.c \
			  count_len.c \
			  print_c_s.c \
			  print_d_i.c \
			  print_p.c \
			  print_x.c \
			  set_format.c \
			  centor.c

BONUS_SRCS	= bonus/all_print_bonus.c \
			  bonus/count_len_bonus.c \
			  bonus/print_c_s_bonus.c \
			  bonus/print_d_i_bonus.c \
			  bonus/print_p_bonus.c \
			  bonus/print_x_bonus.c \
			  bonus/set_format_bonus.c \
			  bonus/centor_bonus.c

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(RM) $(NAME)
	$(AR) $(NAME) $(OBJS)

bonus: .bonus

.bonus: $(BONUS_OBJS)
	$(RM) $(NAME)
	$(AR) $(NAME) $(BONUS_OBJS)
	@touch .bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus