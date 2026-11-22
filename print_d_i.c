/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 13:04:27 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/22 13:34:19 by hzheng2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_d(int num, t_format *data_all)
{
	int		len;
	int		has_sign;
	int		precision_data;
	long	p;

	p = (long) num;
	has_sign = ((*data_all).plus == 1 || (*data_all).space == 1 || p < 0);
	precision_data = (*data_all).precision;
	len = count_len_d(p, (*data_all).precision);
	if ((precision_data < len || precision_data == -1))
		precision_data = len;
	if ((*data_all).minus == 0 && ((*data_all).zero == 0
			|| (*data_all).precision != -1))
		print_char(' ', (*data_all).width - precision_data - has_sign);
	print_plus_space(&p, data_all);
	if (precision_data > len)
		print_char('0', precision_data - len);
	else if ((*data_all).zero == 1 && (*data_all).minus == 0
		&& (*data_all).precision == -1)
		print_char('0', (*data_all).width - precision_data - has_sign);
	print_num(p, len, (*data_all).precision);
	if ((*data_all).minus == 1)
		print_char(' ', (*data_all).width - precision_data - has_sign);
	return (calculatelen(len, (*data_all).width, has_sign, precision_data));
}

int	print_u(unsigned int num, t_format *data_all)
{
	int		len;
	int		precision_data;
	long	p;

	p = (long) num;
	precision_data = (*data_all).precision;
	len = count_len_d(p, (*data_all).precision);
	if ((precision_data < len || precision_data == -1))
		precision_data = len;
	if ((*data_all).minus == 0 && ((*data_all).zero == 0
			|| (*data_all).precision != -1))
		print_char(' ', (*data_all).width - precision_data);
	if (precision_data > len)
		print_char('0', precision_data - len);
	else if ((*data_all).zero == 1 && (*data_all).minus == 0
		&& (*data_all).precision == -1)
		print_char('0', (*data_all).width - precision_data);
	print_num(p, len, (*data_all).precision);
	if ((*data_all).minus == 1)
		print_char(' ', (*data_all).width - precision_data);
	return (calculatelen(len, (*data_all).width, 0, precision_data));
}
