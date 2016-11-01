/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 10:52:00 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/10 12:53:52 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void		ft_if_else(t_env *env, t_main *w)
{
	int		and;
	int		or;

	and = ft_ifindstr(w->line, "&&");
	or = ft_ifindstr(w->line, "||");
	if (and < or)
		ft_and_or(w, env);
	else if (and > or)
		ft_or_and(w, env);
	ft_doublecoms(env, w, 1);
}

void		com_pipes(t_main *w, t_env *env, char **coms)
{
	int	i;

	i = 0;
	coms = ft_strsplit(w->line, ';');
	free(w->line);
	w->line = NULL;
	while (coms[i] != NULL)
	{
		if (ft_strchr(coms[i], '|') == 0)
		{
			w->line = ft_strtrim(coms[i]);
			ft_doublecoms(env, w, 0);
		}
		else if (ft_strchr(coms[i], '|') != 0)
			ft_pipes(env, coms, i, w);
		i++;
	}
	ft_free2d(coms);
	coms = NULL;
}

int			ft_hub(t_env *env, t_main *w)
{
	int		i;
	char	**coms;

	i = 0;
	if (ft_strncmp("exit", w->line, ft_strlen("exit")) == 0)
		ft_exit(env, w);
	else if (ft_findstr("`", w->line) != 0)
		w = ft_bquote(env, w);
	if (ft_findstr("&&", w->line) != 0 && ft_findstr("||", w->line) != 0 &&
			(i = 1))
		ft_if_else(env, w);
	else if (ft_strchr(w->line, '|') != 0 && ft_ifindstr(w->line, "||") == -1)
		com_pipes(w, env, coms);
	else if ((ft_strchr(w->line, '>') != 0 || ft_strchr(w->line, '<') != 0))
		ft_redirect(w, env);
	else if (ft_strchr(w->line, ';') == 0)
		ft_minishell(env, w);
	else if (ft_strchr(w->line, '|') == 0 && ft_strchr(w->line, ';') != 0)
		semicolon(w, env, coms);
	return (i);
}

void		ft_doublecoms(t_env *env, t_main *w, int test)
{
	int			i;
	char		*temp;

	i = 0;
	temp = NULL;
	if (test == 1 && ft_selectinit(w))
	{
		w->line = NULL;
		ft_bzero(w->a[w->y].line, 1024);
		while (ft_select(w, &w->line))
			;
	}
	ft_selectend(w);
	temp = ft_strtrim(w->line);
	free(w->line);
	w->line = ft_strdup(temp);
	free(temp);
	w = ft_keep_main(*w, 0);
	i = ft_hub(env, w);
	if (i == 0 && test == 1)
	{
		free(w->line);
		w->line = NULL;
		ft_doublecoms(env, w, 1);
	}
}
