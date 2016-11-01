/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_support1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 10:00:51 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/10 12:53:36 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int				is_tab_auto_fill1(t_main *e)
{
	DIR				*fd;
	struct dirent	*dp;
	char			t;
	int				x;

	if (!(fd = opendir(e->t.dir)))
	{
		ft_putchar('\n');
		ft_putstr("42sh: error: no such directory ");
		ft_putendl(e->t.dir);
		return (-1);
	}
	while ((dp = readdir(fd)))
	{
		x = ft_strlen(e->t.criteria);
		if (x && ft_strlen(dp->d_name) >= x && ((t = dp->d_name[x]) || 1))
			is_tab_auto_fill2(e, dp, x, t);
		else if (!x && dp->d_name[0] != '.' && (++e->t.h))
		{
			e->t.w = dp->d_namlen * (dp->d_namlen >= e->t.w)\
					+ e->t.w * (dp->d_namlen < e->t.w);
			ft_tabassign(e, ft_strdup(dp->d_name));
		}
	}
	return (1 + 0 * closedir(fd));
}

int				ft_tabprint1(t_main *e)
{
	t_tablst		*t;
	int				x;
	int				y;

	y = 0;
	t = e->t.lst;
	if (!t)
		return (0);
	ft_printf("\n");
	while (t && (x = -1))
	{
		while (t->name[++x])
			ft_putchar(t->name[x]);
		while (y + 1 < e->t.cc && x < e->t.fw + 5 && (++x || 1))
			write(1, " ", 1);
		if (++y == e->t.cc && ((y = 0) || 1) && t->next)
			write(1, "\n", 1);
		t = t->next;
	}
	write(1, "\n", 1);
	return (1);
}

int				ft_tabprint(t_main *e)
{
	struct winsize	win;
	int				x;
	int				y;

	ioctl(0, TIOCGWINSZ, &win);
	e->t.cc = (win.ws_col / (e->t.fw + 5));
	if (e->t.fh != 0 && e->t.cc != 0)
		e->t.lh = (e->t.fh / e->t.cc) + (e->t.fh % e->t.cc > 0);
	if (!e->t.pb || (e->t.lh >= win.ws_row && !ft_tabprintpossibilities(e)))
		return (0);
	return (1);
}

int				ft_tabassign(t_main *e, char *s)
{
	t_tablst	*tmp;

	tmp = (t_tablst *)malloc(sizeof(t_tablst));
	tmp->name = s;
	tmp->next = e->t.tmplst;
	e->t.tmplst = tmp;
	return (0);
}

int				tab_skip(t_main *e)
{
	int			x;

	x = e->cursor;
	e->y += 0;
	while (x < e->a[e->y].x + 1 && e->a[e->y].line[++x]\
			&& (e->a[e->y].line[x] != ' ' && e->a[e->y].line[x] != '\t'))
		;
	e->cursor = x;
	if (!e->a[e->y].line[x] || (e->a[e->y].line[x] != ' '
				&& e->a[e->y].line[x] != '\t'))
	{
		ft_selectinsert(e, ' ');
		e->cursor += (e->cursor < e->a[e->y].x + 1);
	}
	return (0);
}
