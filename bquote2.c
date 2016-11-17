/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquote2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 11:36:02 by kcowle            #+#    #+#             */
/*   Updated: 2016/11/15 11:50:48 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void		reg_bquote(t_env *env, t_main *w, t_bquote bquote)
{
	char	*temp;

	w->line[bquote.i] = '`';
	bquote.promt = (char *)malloc(sizeof(char *) * ft_strlen("bquote> "));
	ft_strcpy(bquote.promt, "bquote> ");
	ft_selectinit(w);
	bquote.str = get_str(bquote.promt, "`", 1);
	ft_selectend(w);
	temp = ft_strnewline(bquote.str);
	bquote.str = temp;
	free(bquote.promt);
	bquote.temp = ft_strdup(w->line);
	free(w->line);
	w->line = (char *)malloc(sizeof(char *) * ft_strlen(bquote.temp) +
			ft_strlen(bquote.str) + 2);
	ft_strcpy(w->line, bquote.temp);
	ft_strcat(w->line, " ");
	ft_strcat(w->line, bquote.str);
	w->line[ft_strlen(w->line)] = '`';
	ft_putchar('\n');
	w = ft_bquote(env, w);
}

t_bquote	ft_bquote_init(t_bquote bquote, t_main *w)
{
	bquote.bk = NULL;
	bquote.buf = (char *)malloc(sizeof(char *) * 3);
	ft_bzero(bquote.buf, 2);
	bquote.num = 0;
	bquote.j = 0;
	bquote.length = 0;
	bquote.temp = NULL;
	bquote.str = (char *)malloc(sizeof(char *) * 2);
	ft_bzero(bquote.str, 2);
	bquote.i = ft_ifindstr(w->line, "`");
	return (bquote);
}

t_bquote	ft_bquote1(t_env *env, char **line, t_bquote bquote)
{
	char *temp;

	temp = *line;
	temp[bquote.i] = '`';
	bquote.line = ft_strsub(temp, bquote.i, bquote.x + 1);
	bquote.coms = ft_strsplit(bquote.line, '\n');
	bquote.length = ft_strlen2d(bquote.coms);
	free(bquote.line);
	return (bquote);
}
