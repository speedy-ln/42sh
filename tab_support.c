/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 09:15:37 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/09 14:50:38 by smahomed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int				tab_getdir(t_main *e)
{
	int		z;
	char	t[2][1024 + 0 * (z = -1)];
	int		y;
	int		x;
	int		ib;

	(ib = -1) && e->t.lb && ft_cleartablines(e);
	e->t.lb = 0;
	e->t.rc = 0;
	ft_bzero(t[1], 1024 + 0 * (e->t.v[0] = 0));
	ft_bzero(t[0], 1024 + 0 * (x = e->cursor));
	if (e->cursor <= e->a[e->y].x && (e->a[e->y].line[e->cursor] != ' '
				&& e->a[e->y].line[e->cursor] != '\t'))
		return (tab_skip(e));
	while (ib < 3 && e->t.v[0] < 2 && e->a[e->y].line[--x] && (y = -1))
	{
		while (ib < 3 && " \t><;|&"[++y] && (e->t.v[0] < 2))
			if (e->a[e->y].line[x] == " \t><;|&"[y])
				ib = (y + 1 + 0 * (y < 2 && (++e->t.v[0])));
		if (ib == -1 && e->a[e->y].line[x] == '/'
				&& ((t[ib + 1][++z] = '\0') || 1))
			z = ++ib - 1;
		ib < 1 && (t[ib + 1][++z] = e->a[e->y].line[x]);
	}
	return (1 + 0 * (tab_getdir1(e, ib, z, t)));
}

void			is_tab_auto_complete(t_main *e)
{
	int			start;
	int			x;
	char		*t;

	x = -1;
	t = 0;
	start = e->cursor;
	start -= (e->a[e->y].line[start] == ' '
			|| e->a[e->y].line[start] == '\t');
	is_tab_auto_complete0(e);
	while (start > -1 && e->a[e->y].line[start] != ' '
			&& e->a[e->y].line[start] != '\t'
			&& e->a[e->y].line[start] != '/')
		start--;
	while (e->a[e->y].line[++start] == e->t.criteria[++x])
		;
	x = e->cursor + 0 * --start;
	while (--x > start && e->a[e->y].line[x] != ' ' &&
			e->a[e->y].line[x] != '\t')
		if (e->a[e->y].x > -1 && e->cursor > 0 && ft_selectbackspace(e))
			e->a[e->y].x -= 1;
	t = &e->t.pos->name[ft_strlen(e->t.criteria)];
	x = -1;
	while (t[++x] && ft_selectinsert(e, t[x]))
		e->cursor += (e->cursor < e->a[e->y].x + 1);
}

int				is_tab_printed(t_main *e)
{
	t_tablst	*t;
	int			tmp;

	e->t.lb = 0;
	e->t.pb = 1;
	e->t.fw = e->t.w;
	e->t.fh = e->t.h;
	while (e->t.lst && ((t = e->t.lst->next) || 1))
	{
		free(e->t.lst->name);
		free(e->t.lst);
		e->t.lst = t;
	}
	e->t.lst = e->t.tmplst;
	e->t.pos = e->t.lst;
	tmp = e->cursor;
	e->cursor = -2;
	ft_printstring(e);
	e->cursor = tmp;
	return (1);
}

int				is_tab_auto_fill(t_main *e)
{
	DIR				fd;
	struct dirent	*dp;
	char			t;
	int				x;

	x = 0;
	if (!is_tab_auto_fill0(e))
		return (0);
	x = ft_strlen(e->t.sd);
	e->t.v[0] = ft_strlen(e->t.criteria);
	e->t.v[0] = e->t.v[0] * (e->t.v[0] <= x) + x * (x < e->t.v[0]);
	if (e->t.criteria && e->t.sd)
		if (e->t.criteria && e->t.criteria[0]
				&& !ft_strncmp(e->t.criteria, e->t.sd, e->t.v[0])
				&& ft_strcmp(e->t.criteria, e->t.sd)
				&& ((x = ft_strlen(e->t.criteria) - 1) || 1))
		{
			while (e->t.sd[++x] && ft_selectinsert(e, e->t.sd[x]))
				e->cursor += (e->cursor < e->a[e->y].x + 1);
			e->t.criteria = e->t.sd;
		}
	return (e->t.h > 0);
}

int				ft_tab(t_main *e)
{
	int		x;

	x = -1;
	while (e->a[e->y].line[++x] &&\
			(e->a[e->y].line[x] == '\t' || e->a[e->y].line[x] == ' '))
		;
	if ((e->t.ctrl_v == 1 || e->cursor < x) && ft_selectinsert(e, '\t'))
		e->cursor += (e->cursor < e->a[e->y].x + 1);
	if (!e->t.ctrl_v && !(e->cursor < x))
	{
		if (!e->t.tb && (tab_getdir(e) && (is_tab_auto_fill(e))))
			is_tab_printed(e);
		else if (e->t.tb && e->t.lst)
			is_tab_auto_complete(e);
	}
	e->t.tb = 1;
	e->t.ctrl_v = 0;
	return (1);
}
