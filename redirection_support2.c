/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_support2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnkadime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 14:44:24 by lnkadime          #+#    #+#             */
/*   Updated: 2016/09/11 14:45:27 by lnkadime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int		get_redirection_count(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '<')
		{
			if (line[i + 1] && line[i + 1] == '<')
				i++;
			count++;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int		append_redirect(char *line, int iteration)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '>')
		{
			count++;
			if (line[i + 1] && line[i + 1] == '>')
			{
				if (iteration == count)
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

void	fd_restore(int fd, int fd2)
{
	dup2(fd, fd2);
	close(fd);
}

void	redirect_stdin(char *file, t_main *w, t_env *env, int extras[])
{
	int		fd;

	fd = open(file, O_RDWR, 0666);
	if (fd == -1)
	{
		ft_putstr("File doesn't exist or cannot be opened.\n");
		ft_strcpy(w->line, " ");
		ft_doublecoms(env, w, 0);
	}
	extras[2] = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (extras[1] == 1)
	{
		ft_doublecoms(env, w, 0);
		fd_restore(extras[2], STDIN_FILENO);
	}
}

void	redirect_stdout(char *file, t_main *w, t_env *env, int extras[])
{
	int		fd;

	if (extras[0] == 1)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fd = open(file, O_RDWR | O_CREAT, 0666);
	extras[3] = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (extras[1] == 1)
	{
		ft_doublecoms(env, w, 0);
		fd_restore(extras[3], STDOUT_FILENO);
	}
}
