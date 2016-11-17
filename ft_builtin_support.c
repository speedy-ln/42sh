/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_support.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 16:43:15 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/11 12:21:14 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int			ft_builtin3(t_env *env, t_main *w)
{
	char	**line2;
	char	*temp;
	int		i;

	i = 0;
	line2 = ft_strsplit(w->line, ' ');
	temp = NULL;
	if (ft_strncmp(w->line, "setenv", 5) == 0 && (i = 1))
	{
		temp = ft_strdup(w->line);
		free(w->line);
		w->line = ft_strtrim(temp);
		ft_free2d(line2);
		line2 = NULL;
		free(temp);
		line2 = ft_strsplit(w->line, ' ');
		env = set_env(line2, env);
	}
	else if (ft_isdigit(w->line[0]) == 1 && w->line[1] == '>'
			&& w->line[2] == '&' && (i = 1))
		ft_fdfuncs(w->line);
	else if (ft_strchr(line2[0], '=') != 0 && (i = 1))
		env = ft_vars(env, w);
	ft_free2d(line2);
	return (i);
}

int			ft_builtin2(t_env *env, t_main *w)
{
	char	**line2;
	int		i;
	char	*temp;

	i = 0;
	line2 = ft_strsplit(w->line, ' ');
	temp = ft_strtrim(line2[0]);
	free(line2[0]);
	line2[0] = NULL;
	line2[0] = (char *)malloc(sizeof(char *) * ft_strlen(temp) + 1);
	ft_strcpy(line2[0], temp);
	free(temp);
	if (ft_strncmp(w->line, "env", 2) == 0 && (i = 1))
		print_env(env);
	else
		i = ft_builtin3(env, w);
	ft_free2d(line2);
	line2 = NULL;
	return (i);
}

t_env		*change_var(t_env *env, char *line)
{
	char	**args;
	int		i;
	char	*tmp;

	args = ft_strsplit(line, '=');
	i = -1;
	while (env->vars[++i] != NULL)
	{
		if (ft_strncmp(args[0], env->vars[i], ft_strlen(args[0])) == 0)
		{
			tmp = ft_strdup(env->vars[i]);
			free(env->vars[i]);
			env->vars[i] = ft_strpaste(tmp, ft_ifindstr(tmp, "=") + 1,
									args[1], ft_strlen(tmp));
			free(tmp);
			ft_free2d(args);
			args = NULL;
			env = ft_keep_struct();
			return (env);
		}
	}
	if (args != NULL)
		ft_free2d(args);
	return (env);
}

char		**temp_return(t_env *env, int *i)
{
	char **temp;

	ft_free2d(temp);
	temp = NULL;
	temp = (char **)malloc(sizeof(char **) * (ft_strlen2d(env->vars) + 2));
	while (env->vars[*i] != NULL)
	{
		temp[*i] = (char*)malloc(sizeof(char*)
								* (ft_strlen(env->vars[*i]) + 1));
		ft_strcpy(temp[*i], env->vars[*i]);
		*i = *i + 1;
	}
	return (temp);
}

t_env		*ft_vars_insert(t_env *env, char **temp, int x, int i)
{
	while (temp[i][x] != '\0' && ft_isprint(temp[i][x]))
		x++;
	if (x == ft_strlen(temp[i]))
	{
		env->vars = (char **)malloc(sizeof(char **) * ft_strlen2d(temp) + 1);
		i = -1;
		while (temp[++i] != NULL)
			env->vars[i] = ft_strdup(temp[i]);
		env->vars[i] = NULL;
	}
	else
		ft_putstr("Only printable characters allowed for the local variable\n");
	return (env);
}
