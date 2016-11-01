/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 10:17:36 by knage             #+#    #+#             */
/*   Updated: 2016/09/10 10:39:47 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

char	*ft_getvar(t_env *env, char *text)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (env->vars)
	{
		while (env->vars[i] != NULL)
		{
			if (ft_strncmp(text, env->vars[i], ft_strlen(text)) == 0)
			{
				ret = ft_strsub(env->vars[i], ft_strlen(text) + 1, \
						ft_strlen(env->vars[i]) - ft_strlen(text) + 1);
				break ;
			}
			i++;
		}
	}
	return (ret);
}

char	*paste_env_var(t_env *env, char *line, int start, int i)
{
	char	*ret;
	char	*temp;
	int		size;

	size = 1;
	while (line[i] != '\0' && line[i] != ' ' && \
			line[i] != '`' && line[i] != '"')
	{
		size++;
		i++;
	}
	if (start != 0)
	{
		temp = ft_strsub(line, start - 1, size);
		ret = ft_getenv(env, temp);
		if (ret != NULL)
		{
			free(temp);
			temp = ft_strpaste(line, start - 1, ret, i);
			free(line);
			line = temp;
			free(ret);
		}
	}
	return (line);
}

char	*is_envvar(char *line, t_env *env)
{
	int		i;
	int		start;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			start = i;
			line = paste_env_var(env, line, start, i);
			i = start - 1;
		}
		i++;
	}
	return (line);
}

char	*variable_check(char *line)
{
	t_env	*env;
	t_main	*main;

	env = ft_keep_struct();
	main = ft_keep_main();
	line = is_history(line, main->a);
	line = is_var(line, env);
	line = is_envvar(line, env);
	return (line);
}
