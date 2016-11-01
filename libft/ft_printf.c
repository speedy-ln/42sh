/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:01:11 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/11 12:25:52 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	print_format2(const char *format, int nb, va_list ap, int *i)
{
	if (format[*i] == 'd' || format[*i] == 'i' || format[*i] == 'D')
		return (ft_putnbr_pf(ap, nb));
	else if (format[*i] == 'c' || format[*i] == 'C')
		return (ft_putchar_pf(ap, nb));
	else if (format[*i] == '\0')
		return ((nb + 0));
	else if (format[*i] == 'l')
		return (ft_putnbrl_pf(ap, format, i));
	else if (format[*i] == 'z')
		return (ft_putz_pf(ap, format, i));
	else if (format[*i] == '%')
	{
		ft_putchar('%');
		return (1);
	}
	else
	{
		ft_putchar('%');
		ft_putchar(format[*i]);
		return (2);
	}
}

static	int	print_format(const char *format, t_c *list, va_list ap, int *i)
{
	int	nb;

	nb = ft_num_whitespaces(i, format);
	ft_print_whitespace(nb);
	while (ft_isdigit(format[*i]))
		*i = *i + 1;
	if (format[*i] == '+' || format[*i] == '-')
	{
		ft_putchar(format[*i]);
		*i += 1;
	}
	while (list->c && list->c != format[*i])
		list++;
	if (list->c)
		return (list->f(ap, nb));
	return (print_format2(format, nb, ap, i));
}

static	t_c	*init_list(void)
{
	t_c	*list;

	list = (t_c *)malloc(sizeof(t_c) * 12);
	list[0].c = 's';
	list[0].f = &ft_putstr_pf;
	list[1].c = 'p';
	list[1].f = &ft_puthexa_pf;
	list[2].c = 'o';
	list[2].f = &ft_putoctal_pf;
	list[3].c = 'x';
	list[3].f = &ft_puthexa_min_pf;
	list[4].c = 'X';
	list[4].f = &ft_puthexa_max_pf;
	list[5].c = 'u';
	list[5].f = &ft_putnbr_u_pf;
	list[6].c = 'U';
	list[6].f = &ft_putnbr_u_pf;
	list[7].c = 'S';
	list[7].f = &ft_putwchar_pf;
	free(list);
	return (list);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	int			printed;
	t_c			*list;

	i = 0;
	printed = 0;
	list = init_list();
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			printed += print_format(format, list, ap, &i);
		}
		else
		{
			ft_putchar(format[i]);
			printed++;
		}
		i++;
	}
	va_end(ap);
	return (printed);
}
