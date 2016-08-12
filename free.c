/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/12 07:51:56 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_free2d(char **array)
{
	int i;

	i = 0;
	if (array[0] != NULL)
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
}
