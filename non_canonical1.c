/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/23 16:58:29 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_select5(t_main *e, char b[4])
{
	if (b[0] == -30 && b[1] == -119 && b[2] == -92)
	{
		if (e->start == -2 && ((e->start = e->cursor) || 1))
			e->end = e->cursor - 1;
		e->cursor--;
		e->end--;
		if (e->start == e->end - 1 && (e->end = -2))
			e->start = -2;
	}
	else if (b[0] == -30 && b[1] == -119 && b[2] == -91)
	{
		if (e->start == -2 && ((e->start = e->cursor - 1) || 1))
			e->end = e->cursor;
		e->cursor += (e->cursor != e->a[e->y].x);
		e->end++;
		if (e->start == e->end - 1 && (e->end = -2))
			e->start = -2;
	}
	else if (!b[1] && (b[0] == 32 || ft_isprint(b[0]))\
			&& (ft_selectinsert(e, b[0])))
		e->cursor += (e->cursor < e->a[e->y].x + 1);
}

int		ft_select4(t_main *e, char b[4])
{
	if (b[0] == 27 && b[1] == 91 && b[2] == 51 && b[3] == 126)
	{
		if (e->a[e->y].x > -1 && e->cursor <= e->a[e->y].x
				&& ft_selectdelete(e))
			--e->a[e->y].x;
	}
	else if (b[0] == -30 && b[1] == -119 && b[2] == -120 && !b[3])
		ft_cut(e);
	else if (b[0] == -61 && b[1] == -89 && !b[2] && !b[3])
		ft_copy(e);
	else if (b[0] == -30 && b[1] == -120 && b[2] == -102 && !b[3])
		ft_paste(e);
	else if (b[0] == 27 && b[1] == 91 && b[2] == 53
			&& b[3] == 126 && e->a[e->y].x > -1)
		e->cursor = 0;
	else if (b[0] == -30 && b[1] == -120 && b[2] == -111 && !b[3])
		ft_ctrlup(e);
	else if (b[0] == -61 && b[1] == -97 && !b[2] && !b[3])
		ft_ctrldown(e);
	else
		ft_select5(e, b);
	return (1);
}

int		ft_select3(t_main *e, char b[4])
{
	if (b[0] == 27 && b[1] == 91 && b[2] == 54 && b[3] == 126)
		e->cursor = e->a[e->y].x + 1;
	else if (b[0] == 27 && b[1] == 91 && b[2] == 72 && !b[3])
	{
		while (e->cursor > 0 && e->a[e->y].line[e->cursor - 1] == ' ')
			e->cursor -= 1;
		while (e->cursor > 0 && e->a[e->y].line[e->cursor - 1] != ' ')
			e->cursor -= 1;
	}
	else if (b[0] == 27 && b[1] == 91 && b[2] == 70 && !b[3])
	{
		while (e->cursor <= e->a[e->y].x
				&& e->a[e->y].line[e->cursor + 1] == ' ')
			e->cursor += 1;
		while (e->cursor <= e->a[e->y].x
				&& e->a[e->y].line[e->cursor + 1] != ' ')
			e->cursor += 1;
		e->cursor = e->cursor * (e->cursor >= e->a[e->y].x)\
					+ (e->cursor + 2) * (e->cursor < e->a[e->y].x);
	}
	else
		ft_select4(e, b);
	return (1);
}

int		ft_select2(t_main *e, char b[4])
{
	if (b[0] == 27 && b[1] == 91 && b[2] == 65 && !b[3] && e->y_cursor > 0)
	{
		ft_strclr(e->a[e->y].line);
		ft_strcat(e->a[e->y].line, e->a[--e->y_cursor].line);
		e->a[e->y].line[e->a[e->y_cursor].x + 1] = '\0';
		e->a[e->y].x = ft_strlen(e->a[e->y].line) - 1;
		e->cursor = e->a[e->y].x + 1;
	}
	else if (b[0] == 27 && b[1] == 91 && b[2] == 66 && !b[3]
			&& e->y_cursor < e->y)
	{
		e->y_cursor + 1 != e->y && (e->a[e->y].line[0] = '\0');
		if (e->y_cursor + 1 == e->y)
			ft_strclr(e->a[e->y].line);
		ft_strcat(e->a[e->y].line, e->a[++e->y_cursor].line);
		e->a[e->y].buff = e->a[e->y_cursor].buff;
		e->a[e->y].x = ft_strlen(e->a[e->y].line);
		e->cursor = e->a[e->y].x + 1;
	}
	else
		ft_select3(e, b);
    e->ctrl_v = (b[0] == 22 && !b[1] && !b[2] && !b[3]);//cntrl v   need to click 2x
	return (1);
}

int		ft_select(t_main *e, char **line)
{
	char	b[8];
	int		tmp;
	char *temp;

	ft_bzero(b, 8 * ft_printstring(e));
	read(0, b, 8);
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
    else if (b[0] == 9 && !b[1])
        return (ft_tab(e));
	else if (b[0] == e->ret && !b[1] && ft_printstring(e + 0 * (e->cursor = -2)))
	{
		temp = (char *)malloc(sizeof(char *) * ft_strlen(e->a[e->y].line) + 1);
		ft_strcpy(temp, e->a[e->y].line);
		free (e->a[e->y].line);
		e->a[e->y].line = ft_strtrim(temp);
		free(temp);
		variable_check(e);
        e->a[e->y].line[e->a[e->y].x + 1] = '\0';
		e->a[e->y].x = ft_strlen(e->a[e->y].line) - 1;
		if (e->line)
			free(e->line);
		e->line = (char *)malloc(sizeof(char *) * ft_strlen(e->a[e->y].line));
		ft_strcpy(e->line, e->a[e->y].line);
		if (e->a[e->y].line)
			free(e->a[e->y].line);
		ft_init(e);
		write(1, "\n", 1);
		return (0);
	}
	return (ft_select2(e, b));
}
