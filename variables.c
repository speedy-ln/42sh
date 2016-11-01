/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 14:01:52 by knage             #+#    #+#             */
/*   Updated: 2016/09/11 12:20:20 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

char	**ft_find_var(t_env *env, char *line, int size)
{
	char	**temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	temp = (char**)malloc(sizeof(char**) * ft_strlen2d(env->vars) + 1);
	while (env->vars[i] != NULL)
	{
		if (ft_strncmp(env->vars[i], line, size) == 0)
			;
		else
		{
			temp[j] = ft_strdup(env->vars[i]);
			j++;
		}
		i++;
	}
	temp[j] = 0;
	return (temp);
}

t_env	*unset_var(t_env *env, char *line)
{
	int		size;
	char	**temp;

	size = ft_strlen(line);
	if (size != 0)
	{
		if (env->vars != NULL)
		{
			temp = ft_find_var(env, line, size);
			ft_free2d(env->vars);
		}
		else
			temp = NULL;
		env->vars = temp;
	}
	return (env);
}

t_env	*export_var(t_env *env, char **line)
{
	char	*value;
	char	**param;

	value = ft_getvar(env, line[1]);
	if (value != NULL)
	{
		param = (char **)malloc(sizeof(char **) * 3);
		param[0] = ft_strdup("setenv");
		param[1] = ft_strdup(line[1]);
		param[2] = value;
		param[3] = 0;
		env = set_env(param, env);
		env = unset_var(env, line[1]);
		free(param[0]);
		free(param[1]);
		free(param[2]);
		free(param);
	}
	return (env);
}
