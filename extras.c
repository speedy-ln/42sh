/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/10 13:32:26 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	free_stuff(t_env *env)
{
	if (env->cmd[0] != NULL)
	{
		ft_free2d(env->cmd);
		env->cmd = NULL;
	}
	if (env->args[0] != NULL)
	{
		ft_free2d(env->args);
		env->args = NULL;
	}
}

t_env	ft_excecute(char **line2, int comcount, t_env *env)
{
	int		i;
	char	*tmp;
	char	*temp;

	*env = ft_slash(env, line2);
	env->args = (char **)malloc(sizeof(char **) * (comcount + 1));
	i = 0;
	while (i < comcount)
	{
		env->args[i] = (char *)malloc(sizeof(char *) * ft_strlen(line2[i]) + 1);
		ft_strcpy(env->args[i], line2[i]);
		i++;
	}
	env->args[i] = NULL;
	execve(env->cmd[0], env->args, &env->enviro[0]);
	free_stuff(env);
	return (*env);
}

char	*gethome(void)
{
	char		*home;
	int			i;
	char		*temp;
	extern char	**environ;

	i = 0;
	home = NULL;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "HOME=", 5) == 0)
		{
			temp = (char *)malloc(sizeof(char *) * (ft_strlen(environ[i]) + 1));
			ft_strcpy(temp, environ[i]);
			home = ft_strnshift(temp, 5);
			free(temp);
			break ;
		}
		i++;
	}
	return (home);
}

void	ft_cd(char *line, t_env *env)
{
	int			change;
	char		*tmp;
	char		*home;
	char		*temp;
	char		pwd[2048];

	change = 1;
	home = gethome();
	getcwd(pwd, 2048);
	tmp = ft_strdup(line);
	temp = ft_strtrim(tmp);
	free(tmp);
	tmp = ft_strnshift(temp, 3);
	free(temp);
	if (tmp[0] == '~')
		change = ft_tilde_cd(change, &tmp, &home);
	else
		change = ft_cd_error(tmp, change, home, env);
	if (change == 1)
	{
		free(env->prev_pwd);
		env->prev_pwd = ft_strdup(pwd);
	}
	free(home);
	free(tmp);
}
