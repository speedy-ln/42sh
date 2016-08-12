/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/12 07:30:51 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int		ft_builtin2(t_env *env, char *line)
{
	char	**line2;
	int		i;

	i = 0;
	line2 = NULL;
	line2 = ft_strsplit(line, ' ');
	line2[0] = ft_strtrim(line2[0]);
	if (ft_strncmp(line, "env", 2) == 0 && (i = 1))
		print_env(env);
	else if (ft_strncmp(line, "setenv", 5) == 0 && (i = 1))
	{
		line = ft_strtrim(line);
		line2 = ft_strsplit(line, ' ');
		env = set_env(line2, env);
	}
	else if (ft_isdigit(line[0]) == 1 && line[1] == '>'
			&& line[2] == '&' && (i = 1))
		ft_fdfuncs(line);
	ft_free2d(line2);
	return (i);
}

int		ft_builtin(t_env *env, char *line)
{
	int		i;
	char	**line2;

	i = 0;
	line2 = NULL;
	line2 = ft_strsplit(line, ' ');
	line2[0] = ft_strtrim(line2[0]);
	if (ft_strcmp(line2[0], "echo") == 0 && (i = 1))
	{
		line = ft_strfcut(line, 5);
		ft_echo(env, line);
	}
	else if (ft_strncmp(line, "cd", 2) == 0 && (i = 1))
		ft_cd(line, env);
	else if (ft_strcmp(line, "clear") == 0 && (i = 1))
		tputs(tgetstr("cl", NULL), 1, ft_ft_putchar);
	else if (ft_strncmp(line, "unsetenv", 7) == 0 && (i = 1))
	{
		line2 = ft_strsplit(line, ' ');
		env = ft_unsetenv(env, line2[1]);
	}
	else if (i == 0)
		i = ft_builtin2(env, line);
	return (i);
}

int		ft_isbuiltin(t_env *env, char *line)
{
	int		i;

	i = 0;
if (ft_findstr(">&", line) == 1 && (i = 1))
		ft_links(line);
	i = ft_builtin(env, line);
	if (i == 1)
		return (0);
	return (1);
}
