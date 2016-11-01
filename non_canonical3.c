/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/09 07:31:06 by knage            ###   ########.fr       */
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
	ft_freet_main(w);
	ft_free(env);
	kill(env->father, SIGTERM);
	ft_putstr("\n\nKILLING NO\n\n");
	pause();
}

int		ft_ctrlup(int cursor, int x)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (x > win.ws_col - 7)
	{
		if (cursor - win.ws_col > -1)
			cursor -= win.ws_col;
		else if (cursor - win.ws_col + 7 > -1)
			cursor = 0;
	}
	return (cursor);
}

int		ft_ctrldown(int cursor, int x)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (cursor + win.ws_col <= x + 1)
		cursor += win.ws_col;
	return (cursor);
}

int		ft_linextention(t_main *e)
{
	if (ft_tabprint(e))
		;
	while (e->lineprom > 0 && ((e->lineprom -= 1) || 1))
		ft_selectlinedel();
	if (e->t.lb && e->t.lh)
		ft_cleartablines(e);
	tputs(tgetstr("dl", 0), 1, ft_ft_putchar);
	tputs(tgetstr("cr", 0), 1, ft_ft_putchar);
	ft_putstr("<<^>>: ");
	return (0);
}
