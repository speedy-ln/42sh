/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/12 07:30:51 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int		ft_selectremalloc(t_main *e)
{
	char	*tmp;
	int		x;

	x = -1;
	e->a[e->y].buff += 1024;
	tmp = (char *)malloc(sizeof(char) * e->a[e->y].buff);
	while (e->a[e->y].line[++x])
		tmp[x] = e->a[e->y].line[x];
	if (e->a[e->y].line)
		free(e->a[e->y].line);
	e->a[e->y].line = tmp;
	return (0);
}

void	ft_exit(t_env *env, t_main *w)
{
	tputs(tgetstr("te", NULL), 1, ft_ft_putchar);
	ft_selectend(w);
	kill(env->father, SIGTERM);
}

int		ft_ctrlup(t_main *e)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (e->a[e->y].x > win.ws_col - 7)
	{
		if (e->cursor - win.ws_col > -1)
			e->cursor -= win.ws_col;
		else if (e->cursor - win.ws_col + 7 > -1)
			e->cursor = 0;
	}
	return (1);
}

int		ft_ctrldown(t_main *e)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	e->cursor += win.ws_col * (e->cursor + win.ws_col <= e->a[e->y].x + 1);
	return (1);
}

int		ft_linextention(t_main *e)
{
	tputs(tgetstr("dl", 0), 1, ft_ft_putchar);
	while (e->lineprom > 0 && ((e->lineprom -= 1) || 1))
	{
		tputs(tgetstr("dl", 0), 1, ft_ft_putchar);
		tputs(tgetstr("up", 0), 1, ft_ft_putchar);
		tputs(tgetstr("cr", 0), 1, ft_ft_putchar);
	}
	tputs(tgetstr("cr", 0), 1, ft_ft_putchar);
	ft_putstr("<<^>>: ");
	return (0);
}
