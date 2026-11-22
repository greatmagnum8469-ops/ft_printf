/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 13:04:37 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/22 13:25:37 by hzheng2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	getnum_untill_not(const char **c)
{
	int	ans;

	ans = 0;
	while (!(**c >= '0' && **c <= '9') && **c != '\0'
		&& !(**c == 'c' || **c == 's' || **c == 'p'
			|| **c == 'd' || **c == 'i' || **c == 'u'
			|| **c == 'x' || **c == 'X' || **c == '%'))
		(*c)++;
	while (**c >= '0' && **c <= '9' && **c != '\0')
	{
		ans *= 10;
		ans += ((**c) - '0');
		(*c)++;
	}
	return (ans);
}

void	reset_t_format(t_format *t)
{
	(*t).precision = -1;
	(*t).width = 0;
	(*t).minus = 0;
	(*t).zero = 0;
	(*t).hash = 0;
	(*t).space = 0;
	(*t).plus = 0;
	(*t).type = 0;
}

int	set_all_bonus_2(const char **c, t_format *data_struct)
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
	if (**c == '0' || **c == '-' || **c == '#'
		|| **c == ' ' || **c == '+')
		return (1);
	else
		return (0);
}

void	set_all_bonus(const char **c, t_format *data_all)
{
	reset_t_format(data_all);
	(*c)++;
	while (**c != '\0')
	{
		if (set_all_bonus_2(c, data_all) == 1)
			(*c)++;
		else if (**c == 'c' || **c == 's' || **c == 'p'
			|| **c == 'd' || **c == 'i' || **c == 'u'
			|| **c == 'x' || **c == 'X' || **c == '%')
		{
			(*data_all).type = **c;
			break ;
		}
		else if (**c == '.')
			(*data_all).precision = getnum_untill_not(c);
		else if ((*((*c)) >= '1' && *((*c)) <= '9'))
			(*data_all).width = getnum_untill_not(c);
		else
			(*c)++;
	}
}
