/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/16 10:40:24 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	semicolon(t_main *w, t_env *env, char **coms)
{
	int	i;

	i = 0;
	coms = ft_strsplit(w->line, ';');
	while (coms[i] != NULL)
	{
		w->line = ft_strtrim(coms[i]);
		ft_minishell(env, w);
		i++;
	}
}

void	com_pipes(t_main *w, t_env *env, char **coms)
{
	int	i;

	i = 0;
	coms = ft_strsplit(w->line, ';');
	while (coms[i] != NULL)
	{
		if (ft_strchr(coms[i], '|') == 0)
		{
			w->line = ft_strtrim(coms[i]);
			ft_minishell(env, w);
		}
		else if (ft_strchr(coms[i], '|') != 0)
			ft_pipes(env, coms, i, w);
		i++;
	}
}

void	ft_doublecoms(t_env *env, t_main *w)
{
	char		**coms;
	int 		i;

	i = 0;
	coms = NULL;
	w->line = NULL;
	ft_selectinit(w);
	while (ft_select(w, &w->line))
		;
	ft_selectend(w);
	w = ft_keep_main(*w, 0);
	if (ft_strchr(w->line, '>') != 0 || ft_strchr(w->line, '<') != 0)
		ft_redirect(w, env);
	if (ft_strchr(w->line, ';') == 0 && ft_strchr(w->line, '|') == 0)
		ft_minishell(env, w);
	else if (ft_strchr(w->line, '|') == 0 && ft_strchr(w->line, ';') != 0)
		semicolon(w, env, coms);
	else if (ft_strchr(w->line, '|') != 0)
		com_pipes(w, env, coms);
	if (i == 0)
		ft_doublecoms(env, w);
}
