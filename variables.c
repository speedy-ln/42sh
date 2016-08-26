/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 14:01:52 by knage             #+#    #+#             */
/*   Updated: 2016/08/23 16:25:35 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

t_env	*unset_var(t_env *env,  char *line)
{
	int 	i;
	int 	j;
	int		size;
	char	**temp;

	i = 0;
	j = 0;
	size = ft_strlen(line);
	if (size != 0)
	{
		temp = (char**)malloc(sizeof(char**) * ft_strlen2D(env->vars) + 1);
		if (env->vars != NULL)
		{
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
			ft_free2d(env->vars);
		}
		temp[j] = 0;
		env->vars = temp;
	}
	return (env);
}

t_env   *export_var(t_env *env, char **line)
{
    char *value;
    char **param;
    
    value = ft_getvar(env, line[1]);
    if (value != NULL)
    {
        param = (char **)malloc(sizeof(char**) * 4);
		param[0] = ft_strdup("setenv");
        param[1] = line[1];
        param[2] = value;
        param[3] = 0;
        env = set_env(param, env);
        env = unset_var(env, line[1]);
//        ft_free2d(param);
    }
    return (env);
}
