/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/18 10:29:04 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

t_env	ft_excecute(char **line2, int comcount, t_env *env)
{
	int		i;
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
	free(newline);
	if (env->cmd[0] != NULL)
		ft_free2d(env->cmd);
	if (env->args[0] != NULL)
		ft_free2d(env->args);
	return (*env);
}

char	*gethome(void)
{
	char		*home;
	int			i;
	extern char	**environ;

	i = 0;
	home = NULL;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "HOME=", 5) == 0)
		{
			home = (char *)malloc(sizeof(char *) * (ft_strlen(environ[i]) + 1));
			ft_strcpy(home, environ[i]);
			home = ft_strnshift(home, 5);
			break ;
		}
		i++;
	}
	return (home);
}

void	ft_cd(char *line, t_env *env)
{
	int			i;
	int			change;
	char		*tmp;
	char		*home;
	char		pwd[2048];

	i = 0;
	change = 1;
	home = gethome();
	getcwd(pwd, 2048);
	tmp = (char *)malloc(sizeof(char *) * (ft_strlen(line) + 1));
	ft_strcpy(tmp, line);
	tmp = ft_strrw(tmp);
	tmp = ft_strnshift(tmp, 3);
	i = 0;
	if (tmp[0] == '~')
	{
		tmp = ft_strnshift(tmp, 1);
		while (tmp[0] == '/')
			tmp = ft_strnshift(tmp, 1);
		home = ft_strjoin(home, "/");
		home = ft_strjoin(home, tmp);
		if (chdir(home) == -1)
		{
			ft_putstr("No such file or directory.\n");
			change = 0;
		}
	}
	else if (tmp[0] == 0)
		chdir(home);
	else if (tmp[0] == '-')
		chdir(env->prev_pwd);
	else if (chdir(tmp) == -1)
	{
		ft_putstr("No such file or directory.\n");
		change = 0;
	}
	if (change == 1)
	{
		free(env->prev_pwd);
		env->prev_pwd = (char*)malloc(sizeof(char*) * ft_strlen(pwd));
		ft_strcpy(env->prev_pwd, pwd);
	}
	free(home);
	free(tmp);
}

int		get_dir2(t_env *env, char **line2, char **line)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	int				i;

	i = 0;
	while (line2[++i] != NULL && ft_strcpy(line2[i], ft_strcat(line2[i], "/")))
	{
		pdir = opendir(line2[i]);
		while (pdir != NULL && (pdirent = readdir(pdir)) != NULL)
			if (ft_strcmp(pdirent->d_name, line[0]) == 0)
			{
				env->path = (char *)malloc(sizeof(char *) \
						* ft_strlen(line2[i]) + 1);
				ft_strcpy(env->path, line2[i]);
				return (1);
			}
	}
	return (0);
}

t_env	get_dir(t_env *env, char **line)
{
	char			*linel;
	char			**line2;
	char			**tdir;

	linel = get_path(env);
	ft_strcpy(linel, ft_strfcut(linel, 5));
	line2 = ft_strsplit(linel, ':');
	free(linel);
	if (line[0][0] == '/')
	{
		ft_putstr("test\n\n");
		tdir = ft_strsplit(line[0], '/');
		env->path = (char *)malloc(sizeof(char *) * ft_strlen(tdir[0]));
		env->path[0] = '/';
		ft_strcat(env->path, tdir[0]);
		ft_strcat(env->path, "/");
		return (*env);
	}
	if (get_dir2(env, line2, line))
		return (*env);
	ft_putstr(line[0]);
	ft_putstr(": command not found.\n");
	return (*env);
}
