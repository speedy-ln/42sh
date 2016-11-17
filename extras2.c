/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 10:12:50 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/09 14:09:52 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void			ft_and_or(t_main *w, t_env *env)
{
	char		**line2;

	line2 = ft_strsplit(w->line, '&');
	free(w->line);
	w->line = ft_strdup(line2[0]);
	ft_doublecoms(env, w, 0);
	ft_free2d(line2);
	line2 = NULL;
	line2 = ft_strsplit(line2[1], '|');
	free(w->line);
	if (WIFEXITED(env->father) != 0)
		w->line = ft_strdup(line2[0]);
	else
		w->line = ft_strdup(line2[1]);
	if (line2 != NULL)
	{
		ft_free2d(line2);
		line2 = NULL;
	}
	ft_doublecoms(env, w, 0);
}

void			ft_or_and(t_main *w, t_env *env)
{
	char		**line2;

	line2 = ft_strsplit(w->line, '|');
	free(w->line);
	w->line = ft_strdup(line2[0]);
	ft_doublecoms(env, w, 0);
	ft_free2d(line2);
	line2 = ft_strsplit(line2[1], '&');
	free(w->line);
	if (WIFEXITED(env->father) == 0)
		w->line = ft_strdup(line2[0]);
	else
		w->line = ft_strdup(line2[1]);
	ft_free2d(line2);
	ft_doublecoms(env, w, 0);
}
