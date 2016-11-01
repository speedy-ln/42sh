/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 10:38:57 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/01 10:39:53 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int		ft_cd_error(char *tmp, int change, char *home, t_env *env)
{
	if (tmp[0] == 0)
		chdir(home);
	else if (tmp[0] == '-')
		chdir(env->prev_pwd);
	else if (chdir(tmp) == -1 && (change = 0) == 0)
		ft_putstr("No such file or directory.\n");
	return (change);
}

int		ft_tilde_cd(int change, char **tmp, char **home)
{
	*tmp = ft_strnshift(*tmp, 1);
	while (*tmp[0] == '/')
		*tmp = ft_strnshift(*tmp, 1);
	*home = ft_strjoin(*home, "/");
	*home = ft_strjoin(*home, *tmp);
	if (chdir(*home) == -1 && (change = 0) == 0)
		ft_putstr("No such file or directory.\n");
	return (change);
}

t_env	ft_slash(t_env *env, char **line2)
{
	char	*newline;

	if (line2[0][0] != '/')
	{
		newline = (char *)malloc(sizeof(char *) *
		(sizeof(env->path) + sizeof(line2[0]) + 1));
		ft_strcpy(newline, env->path);
		env->cmd = (char **)malloc(sizeof(char **) * 5);
		env->cmd[0] = (char *)malloc(sizeof(char *) * \
		(sizeof(newline) + sizeof(line2[0]) + 1));
		ft_strcpy(env->cmd[0], ft_strcat(newline, line2[0]));
	}
	else
	{
		newline = (char *)malloc(sizeof(char *) * ft_strlen(line2[0]) + 1);
		env->cmd = (char **)malloc(sizeof(char **) * 5);
		env->cmd[0] = (char *)malloc(sizeof(char *) * sizeof(line2[0]) + 1);
		ft_strcpy(env->cmd[0], line2[0]);
	}
	free(newline);
	return (*env);
}
