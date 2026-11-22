/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 13:04:11 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/22 13:04:11 by hzheng2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_format
{
	int		precision;
	int		width;
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	char	type;
}				t_format;

int		ft_printf(const char *c, ...);
int		print_something(t_format *data_all, va_list *arg_ptr);

int		getnum_untill_not(const char **c);
void	reset_t_format(t_format *t);
int		set_all_bonus_2(const char **c, t_format *data_struct);
void	set_all_bonus(const char **c, t_format *data_all);

int		len_of_str(char *c);
void	print_str(char *c, int precision);
void	print_char(char c, int len);
int		calculatelen(int len, int width_data, int has_sign, int precision_data);
int		count_len_d(long p, int precision);
void	print_num(long p, int len, int precision);
void	print_plus_space(long *p, t_format *data_all);

int		print_c(char c, t_format *data_all);
int		print_s(char *c, t_format *data_all);
int		print_d(int num, t_format *data_all);
int		print_u(unsigned int num, t_format *data_all);

int		print_p_recur(unsigned long p);
int		count_len_p(unsigned long p);
int		print_p(unsigned long p, t_format *data_all);

int		recure_print_hex(unsigned long p, t_format *data_all);
void	print_0X(unsigned long p, t_format *data_all);
int		count_len_x(unsigned int p, t_format *data_all);
int		print_x(unsigned int p, t_format *data_all);

#endif