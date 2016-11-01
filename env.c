/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 13:35:18 by knage             #+#    #+#             */
/*   Updated: 2016/09/11 12:21:40 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	print_env(t_env *env)
{
	int i;

	i = 0;
	while (env->enviro[i] != NULL)
	{
		ft_putstr(env->enviro[i]);
		ft_putchar('\n');
		i++;
	}
}

t_env	setenvhelp(t_env *env, int i, char **line2)
{
	char	*temp;

	free(env->enviro[i]);
	temp = ft_strjoin(line2[1], "=");
	env->enviro[i] = ft_strjoin(temp, line2[2]);
	free(temp);
	env = ft_keep_struct(env);
	return (*env);
}

t_env	*set_envhelper(t_env *env, int i, char **line2)
{
	char	**envirok;
	char	*temp;

	envirok = (char **)malloc(sizeof(char **) * i + 2);
	i = -1;
	while (line2[1] && env->enviro[++i] != NULL)
		envirok[i] = ft_strdup(env->enviro[i]);
	temp = ft_strjoin(line2[1], "=");
	envirok[i] = ft_strjoin(temp, line2[2]);
	free(temp);
	envirok[++i] = NULL;
	ft_free2d(env->enviro);
	env->enviro = envirok;
	return (env);
}

t_env	*set_env(char **line2, t_env *env)
{
	int		i;

	i = -1;
	if (ft_strlen2d(line2) == 3)
	{
		while (line2[1] && env->enviro[++i] != NULL)
			if (ft_strncmp(line2[1], env->enviro[i], \
						ft_strlen(line2[1]) - 1) == 0)
			{
				*env = setenvhelp(env, i, line2);
				return (env);
			}
		if (i != 0)
			env = set_envhelper(env, i, line2);
	}
	return (env);
}

t_env	*ft_unsetenv(t_env *env, char *line)
{
	int		i;
	int		j;
	int		size;
	char	**temp;

	j = 0;
	size = ft_strlen(line);
	if (size != 0)
	{
		i = ft_strlen2d(env->enviro);
		temp = (char **)malloc(sizeof(char **) * i + 1);
		i = -1;
		while (env->enviro[++i] != NULL)
		{
			if (ft_strncmp(env->enviro[i], line, size) == 0)
				;
			else
				temp[j++] = ft_strdup(env->enviro[i]);
		}
		ft_free2d(env->enviro);
		temp[j] = NULL;
		env->enviro = temp;
	}
	return (env);
}
