/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 10:17:36 by knage             #+#    #+#             */
/*   Updated: 2016/08/22 08:11:37 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

char	*is_history(char *str, t_21line_l *history)
{
    int 	i;
    int 	start;
    int		pos;
    int		yes;
    char	*prev;
    char	*after;
    
    i = 0;
    start = 0;
    pos = 0;
    yes = 0;
    while (str[i])
    {
        if (str[i] == '!' && ft_isnbr(str[i + 1]))
        {
            start = i;
            i++;
            while (ft_isnbr(str[i]))
                i++;
            pos = ft_atoi(ft_strsub(str, start + 1, i - start));
            pos -= 1;
            if (history[pos].line[0] != '\0')
            {
                prev = ft_strsub(str, 0, start);
                after = ft_strsub(str, i, ft_strlen(str) - i);
                free(str);
                str = ft_strjoin(prev, history[pos].line);
                str = ft_strjoin(str, after);
                free(prev);
                free(after);
                yes = 1;
            }
        }
        i++;
    }
    if (yes == 1)
        ft_printf("\n%s\n", str);
    return (str);
}

char	*ft_getvar(t_env *env, char *text)
{
	int     i;
	char    *ret;

	i = 0;
	ret = NULL;
	if (env->vars)
	{
		while (env->vars[i] != NULL)
		{
			if (ft_strncmp(text, env->vars[i], ft_strlen(text)) == 0)
			{
				ret = ft_strsub(env->vars[i], ft_strlen(text) + 1, ft_strlen(env->vars[i]) - ft_strlen(text) + 1);
				break;
			}
			i++;
		}
	}
	return(ret);
}

char    *is_envvar(char *line, t_env *env)
{
	int     i;
	int     size;
	int     start;
	char    *ret;
	char    *temp;

	i = 0;
	ret = NULL;
	temp = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			start = i;
			size = 1;
			while (line[i] != '\0' && line[i] != ' ')
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
			i = start - 1;
		}
		i++;
	}
	return (line);
}

char    *is_var(char *line, t_env *env)
{
	int     i;
	int     size;
	int     start;
	char    *ret;
	char    *temp;

	i = 0;
	ret = NULL;
	temp = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			start = i;
			size = 1;
			while (line[i] != '\0' && line[i] != ' ')
			{
				size++;
				i++;
			}
			if (start != 0)
			{
				temp = ft_strsub(line, start, size);
				ret = ft_getvar(env, temp);
				if (ret != NULL)
				{
					free(temp);
					temp = ft_strpaste(line, start - 1, ret, i);
					free(line);
					line = temp;
					free(ret);
				}
			}
			i = start - 1;
		}
		i++;
	}
	return (line);
}

void    variable_check(t_main *env)
{
	t_env *en;

	en = ft_keep_struct();
	env->a[env->y].line = is_history(env->a[env->y].line, env->a);
	env->a[env->y].line = is_var(env->a[env->y].line, en);
	env->a[env->y].line = is_envvar(env->a[env->y].line, en);
}
