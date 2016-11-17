/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 13:17:35 by knage             #+#    #+#             */
/*   Updated: 2016/11/15 12:15:45 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int		get_dir2(t_env *env, char **line2, char **line)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	int				i;
	char			*temp;

	temp = NULL;
	i = 0;
	while (line2[i] != NULL)
	{
		temp = ft_strjoin(line2[i], "/");
		line2[i] = ft_strdup(temp);
		pdir = opendir(line2[i]);
		while (pdir != NULL && (pdirent = readdir(pdir)) != NULL)
		{
			if (ft_strcmp(pdirent->d_name, line[0]) == 0)
			{
				env->path = (char *)malloc(sizeof(char *) \
						* ft_strlen(line2[i]) + 1);
				ft_strcpy(env->path, line2[i]);
				return (1);
			}
		}
		i++;
	}
	free(pdir);
	return (0);
}

t_env	path_management(char **line, char **tdir, t_env *env, char **line2)
{
	tdir = ft_strsplit(line[0], '/');
	env->path = (char *)malloc(sizeof(char *) * ft_strlen(tdir[0]));
	env->path[0] = '/';
	ft_strcat(env->path, tdir[0]);
	ft_strcat(env->path, "/");
	if (line2 != NULL)
	{
		ft_free2d(line2);
		line2 = NULL;
	}
	return (*env);
}

void	command_not_found(char **line, char **line2, t_env *env)
{
	t_main			*w;

	ft_putstr(line[0]);
	ft_putstr(": command not found.\n");
	if (line2[0] != NULL && line2 != NULL)
	{
		ft_free2d(line2);
		line2 = NULL;
	}
	w = ft_keep_main();
	ft_doublecoms(env, w, 1);
}

t_env	get_dir(t_env *env, char **line)
{
	char			*linel;
	char			**line2;
	char			**tdir;
	char			*temp;

	linel = get_path(env);
	temp = ft_strfcut(linel, 5);
	free(linel);
	linel = temp;
	line2 = ft_strsplit(linel, ':');
	free(linel);
	if (line[0][0] == '/')
		return (path_management(line, tdir, env, line2));
	if (get_dir2(env, line2, line))
	{
		if (line2 != NULL)
		{
			ft_free2d(line2);
			line2 = NULL;
		}
		return (*env);
	}
	command_not_found(line, line2, env);
	return (*env);
}
