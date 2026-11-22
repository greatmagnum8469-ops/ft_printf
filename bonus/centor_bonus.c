/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 13:04:05 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/22 15:00:27 by hzheng2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_something(t_format *data_all, va_list *arg_ptr)
{
	if ((*data_all).type == 'c')
		return (print_c((char)va_arg(*arg_ptr, int), data_all));
	else if ((*data_all).type == 's')
		return (print_s(va_arg(*arg_ptr, char *), data_all));
	else if ((*data_all).type == 'p')
		return (print_p((unsigned long)(va_arg(*arg_ptr, void *)), data_all));
	else if ((*data_all).type == 'd' || (*data_all).type == 'i')
		return (print_d(va_arg(*arg_ptr, int), data_all));
	else if ((*data_all).type == 'u')
		return (print_u(va_arg(*arg_ptr, unsigned int), data_all));
	else if ((*data_all).type == 'x')
		return (print_x(va_arg(*arg_ptr, unsigned int), data_all));
	else if ((*data_all).type == 'X')
		return (print_x(va_arg(*arg_ptr, unsigned int), data_all));
	else if ((*data_all).type == '%')
		return (print_c('%', data_all));
	return (0);
}

int	ft_printf(const char *c, ...)
{
	va_list		arg_ptr;
	t_format	data_all;
	int			len;

	va_start(arg_ptr, c);
	len = 0;
	while (*c != '\0')
	{
		if (*c == '%' && *(c + 1) != '\0')
		{
			set_all_bonus(&c, &data_all);
			len += print_something(&data_all, &arg_ptr);
		}
		else
		{
			len += 1;
			write(1, c, 1);
		}
		if (*c != '\0')
			c++;
	}
	va_end(arg_ptr);
	return (len);
}
