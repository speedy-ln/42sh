/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/23 08:36:59 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int		ft_ft_putchar(int c)
{
	return (write(2, &c, 1));
}

int		ft_cursor(char c)
{
	tputs(tgetstr("so", 0), 1, ft_ft_putchar);
	if (c == '\t')
		write(1, " ", 1);
	else
		ft_putchar(c);
	tputs(tgetstr("se", 0), 1, ft_ft_putchar);
	if (c == '\t')
		write(1, "   ", 3);
	return (0);
}

int		ft_selectdelete(t_main *e)
{
	int		x;

	x = e->cursor - 1;
	while (++x < e->a[e->y].x)
		e->a[e->y].line[x] = e->a[e->y].line[x + 1];
	e->a[e->y].line[e->a[e->y].x] = '\0';
	return (1);
}

int		ft_selectbackspace(t_main *e)
{
	int		x;

	x = --e->cursor - 1;
	while (++x < e->a[e->y].x)
		e->a[e->y].line[x] = e->a[e->y].line[x + 1];
	e->a[e->y].line[e->a[e->y].x] = '\0';
	return (1);
}

int		ft_selectinsert(t_main *e, char c)
{
	int		x;

	x = ++e->a[e->y].x;
	while (--x >= e->cursor)
		e->a[e->y].line[x + 1] = e->a[e->y].line[x];
	e->a[e->y].line[x + 1] = c;
	return (1);
}
