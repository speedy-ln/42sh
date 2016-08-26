/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/23 16:01:05 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_free2d(char **array)
{
	int i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	ft_free(t_env *env)
{
	int i;

	i = 0;
	while (env->enviro[i] != NULL)
	{
		free(env->enviro[i]);
		i++;
	}
	free(env->enviro[i]);
	i = 0;
	while (env->envirobk[i] != NULL)
	{
		free(env->envirobk[i]);
		i++;
	}
	free(env->envirobk[i]);
	if (env->path)
		free(env->path);
	if (env->cmd)
		ft_free2d(env->cmd);
	if (env->args)
		ft_free2d(env->args);
	if (env->env)
		ft_free2d(env->env);
	if (env->history)
		ft_free2d(env->history);
	if (env->prev_pwd)
		free(env->prev_pwd);
	if (env->vars)
		ft_free2d(env->vars);
}

void	ft_freet_main(t_main *w)
{
	ft_putstr("FREEING THE LINE NOW");
	if (w->line != NULL)
		free(w->line);
	if (w->line2 != NULL)
		ft_free2d(w->line2);
	if (w->clip != NULL)
		free(w->clip);
	if (w->pro != NULL)
		free(w->pro);
}
