/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 07:06:55 by knage             #+#    #+#             */
/*   Updated: 2016/09/09 07:09:28 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_print_chars(t_main *e, int x)
{
	if (e->start != -2 && x > e->start && x < e->end)
		select_c(e->a[e->y].line[x]);
	else if (e->start != -2 && x < e->start && x > e->end)
		select_c(e->a[e->y].line[x]);
	else if (x == e->cursor)
		ft_cursor(e->a[e->y].line[x]);
	else
	{
		if (e->a[e->y].line[x] == '\t')
			write(1, "    ", 4);
		else
			ft_putchar(e->a[e->y].line[x]);
	}
}

int		ft_printstring(t_main *e)
{
	struct winsize	win;
	int				x;
	int				t[3];

	ioctl(0 * ((t[0] = win.ws_col) || 1), TIOCGWINSZ, &win);
	x = -1 + 0 * ft_linextention(e);
	t[1] = 7;
	e->lineprom = 0;
	while (++x <= e->a[e->y].x && ((t[1] += 1) || 1))
	{
		e->lineprom += (t[1] == t[0]);
		t[1] = t[1] * (t[1] < t[0]);
		if (e->a[e->y].line[x])
			ft_print_chars(e, x);
	}
	e->cursor == e->a[e->y].x + 1 && ft_cursor(' ');
	return (1 + 0 * (ft_tabprint(e) && (e->t.lb = 1) && (ft_tabprint1(e))));
}
