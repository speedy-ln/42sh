/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 10:15:31 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/10 13:11:25 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

t_bquote		ft_bquote2(t_bquote bquote)
{
	if (bquote.j == 0)
	{
		while (bquote.coms[bquote.j][0] != '`')
			bquote.coms[bquote.j]++;
		bquote.coms[bquote.j]++;
	}
	if (bquote.j == bquote.length - 1)
		bquote.coms[bquote.j][ft_strlen(bquote.coms[bquote.j]) - 1] = '\0';
	return (bquote);
}

t_bquote		ft_bquote3(t_env *env, t_main *w, t_bquote bquote)
{
	bquote = ft_bquote2(bquote);
	pipe(bquote.fd);
	if (((env->father = fork()) || 1) && env->father == 0)
	{
		dup2(bquote.fd[1], STDOUT);
		close(bquote.fd[0]);
		w->line = ft_strdup(bquote.coms[bquote.j]);
		ft_doublecoms(env, w, 0);
		exit(0);
	}
	else
	{
		close(bquote.fd[1] + 0 * wait(NULL));
		bquote.str = ft_strdup(" ");
		while (read(bquote.fd[0], bquote.buf, 1) != 0)
		{
			bquote.temp = ft_strjoin(bquote.str, bquote.buf);
			free(bquote.str);
			bquote.str = bquote.temp;
		}
		bquote.temp = ft_strtrim(bquote.str);
		free(bquote.str);
		bquote.str = bquote.temp;
	}
	return (bquote);
}

t_bquote		ft_bquote4(t_bquote bquote)
{
	if (bquote.bk == NULL)
		bquote.bk = bquote.str;
	else
	{
		bquote.temp = ft_strjoin(bquote.bk, " ");
		free(bquote.bk);
		bquote.bk = ft_strdup(bquote.temp);
		free(bquote.temp);
		bquote.temp = ft_strjoin(bquote.bk, bquote.str);
		free(bquote.bk);
		free(bquote.str);
		bquote.bk = bquote.temp;
	}
	return (bquote);
}

int				ft_bquote_support(t_env *env, t_main *w, t_bquote bquote)
{
	w->line[bquote.i] = '*';
	bquote.x = ft_ifindstr(w->line, "`");
	if (bquote.x != -1)
	{
		bquote = ft_bquote1(env, &w->line, bquote);
		while (bquote.j != bquote.length)
		{
			bquote = ft_bquote3(env, w, bquote);
			if (((bquote.j++) || 1) && env->fail != 1)
				bquote = ft_bquote4(bquote);
			else
				env->fail = 0;
		}
		bquote.temp = ft_strnewline(bquote.bk);
		free(bquote.bk);
		bquote.bk = ft_strdup(bquote.temp);
		free(bquote.temp);
		bquote.temp = ft_strpaste(w->line, bquote.i, bquote.bk, bquote.x + 1);
		free(w->line);
		w->line = ft_strdup(bquote.temp);
		free(bquote.temp);
		ft_ifindstr(w->line, "`") != -1 && (w = ft_bquote(env, w));
		return (1);
	}
	return (0);
}

t_main			*ft_bquote(t_env *env, t_main *w)
{
	t_bquote	bquote;

	bquote = ft_bquote_init(bquote, w);
	env->fail = 0;
	if (bquote.i != -1)
	{
		if (ft_bquote_support(env, w, bquote) == 0)
			reg_bquote(env, w, bquote);
	}
	return (w);
}
