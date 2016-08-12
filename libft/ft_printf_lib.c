/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lib.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:01:11 by kcowle            #+#    #+#             */
/*   Updated: 2016/08/07 16:01:21 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_num_whitespaces(int *i, const char *format)
{
	int		num_whitespaces;

	num_whitespaces = 0;
	if (format[*i] == ' ')
	{
		num_whitespaces = 1;
		*i += 1;
		while (format[*i] && format[*i] == ' ')
		{
			num_whitespaces += 1;
			*i += 1;
		}
	}
	return (num_whitespaces);
}

void	ft_print_whitespace(int n)
{
	while (n > 0)
	{
		ft_putchar(' ');
		n--;
	}
}
