/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_support2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 10:34:17 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/10 11:00:44 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int			is_tab_auto_fill2(t_main *e, struct dirent *dp, int x, int t)
{
	dp->d_name[x] = '\0';
	if (dp->d_name[0] != '.' && !ft_strcmp(e->t.criteria, dp->d_name)\
			&& ((dp->d_name[x] = t) || 1))
	{
		x = -1;
		++e->t.h == 1 && (e->t.sd = ft_strdup(dp->d_name));
		while (e->t.sd[++x] && dp->d_name[x] && e->t.sd[x] == dp->d_name[x])
			;
		e->t.sd[x] && (e->t.sd[x] = '\0');
		e->t.w = dp->d_namlen * (dp->d_namlen >= e->t.w) + e->t.w *\
				(dp->d_namlen < e->t.w);
		ft_tabassign(e, ft_strdup(dp->d_name));
	}
	dp->d_name[x] = t;
	return (0);
}

int			tab_getdir1(t_main *e, int ib, int z, char t[2][1024])
{
	int		x;
	int		y;

	e->t.criteria = (char *)malloc(sizeof(char) * ft_strlen(t[0]));
	e->t.dir = (char *)malloc(sizeof(char) * ft_strlen(t[1]));
	x = -1;
	y = ft_strlen(t[0]);
	e->t.dir[++z] = '\0';
	e->t.criteria[y] = '\0';
	while (--z > -1 && t[1][z])
		e->t.dir[++x] = t[1][z];
	z = -1;
	while (t[0][++z])
		e->t.criteria[--y] = t[0][z];
	if ((ib <= 0 || ib >= 5) && (ft_strlen(e->t.dir) == 0) && (e->t.rc = 1))
	{
		free(e->t.dir);
		ft_strcpy(e->t.dir, "/usr/bin/");
	}
	else if (ib >= 1 && ib < 5 && (ft_strlen(e->t.dir) == 0))
	{
		free(e->t.dir);
		ft_strcat(e->t.dir, "./");
	}
	return (1);
}

int			ft_tabprintpossibilities(t_main *e)
{
	char	c;

	ft_printf("\n42sh: do you wish to see all %d\
			possibilities (%d lines)?", e->t.fh, e->t.lh);
	read(0, &c, 1);
	ft_selectlinedel();
	e->t.pb = 0;
	if (c == 'y' && ft_tabprint1(e))
		return (1);
	return (0);
}

int			ft_selectlinedel(void)
{
	tputs(tgetstr("dl", 0), 1, ft_ft_putchar);
	tputs(tgetstr("up", 0), 1, ft_ft_putchar);
	return (1 + 0 * tputs(tgetstr("cr", 0), 1, ft_ft_putchar));
}

int			ft_cleartablines(t_main *e)
{
	while (--e->t.lh + 1 > -1)
		ft_selectlinedel();
	return (1);
}
