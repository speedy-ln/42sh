/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 07:20:50 by knage             #+#    #+#             */
/*   Updated: 2016/09/10 11:02:06 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_cursor_moves(t_main *e, char *b)
{
	int		tmp;

	tmp = 0;
	if (ft_isprint(b[0]) && e->a[e->y].x >= e->a[e->y].buff)
		ft_selectremalloc(e);
	else if (b[0] == 127 && e->a[e->y].x > -1
			&& e->cursor > 0 && ft_selectbackspace(e))
		tmp += 0 * (--e->a[e->y].x);
	else if (b[0] == 27 && b[1] == 91 && b[2] == 67
			&& b[3] == 0 && (e->start = -2))
		tmp += 0 * (e->cursor += (e->cursor < e->a[e->y].x + 1));
	else if (b[0] == 27 && b[1] == 91 && b[2] == 68
			&& b[3] == 0 && (e->start = -2))
		e->cursor -= (e->cursor > 0);
}

int		ft_return_line(t_main *e, char *b)
{
	if (b[0] == e->ret && !b[1])
	{
		e->t.lb && ft_cleartablines(e) && (e->t.lb = 0);
		tputs(tgetstr("dl", 0), 1, ft_ft_putchar);
		tputs(tgetstr("cr", 0), 1, ft_ft_putchar);
		ft_putstr("<<^>>: ");
		ft_putstr(e->a[e->y].line);
		e->a[e->y].line = variable_check(e->a[e->y].line);
		e->a[e->y].line[e->a[e->y].x + 1] = '\0';
		e->a[e->y].x = ft_strlen(e->a[e->y].line) - 1;
		if (e->line)
			free(e->line);
		e->line = ft_strtrim(e->a[e->y].line);
		ft_init(e);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

int		ft_select(t_main *e, char **line)
{
	char	b[8];
	char	*temp;

	ft_bzero(b, 8 * ft_printstring(e));
	read(0, b, 8);
	ft_cursor_moves(e, b);
	if (b[0] == 9 && !b[1])
		return (ft_tab(e));
	if (ft_return_line(e, b) == 1)
		return (0);
	return (ft_select2(e, b));
}
