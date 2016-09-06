/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/12 07:30:51 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_redirect(t_main *w, t_env *env)
{
	int		append;

	append = 0;
	if (ft_strchr(w->line, '>') != 0)
	{
		if (ft_findstr(">>", w->line))
			append = 1;
		redirection_gt(w, env, append);
	}
	else if (ft_strchr(w->line, '<') != 0)
		redirection_lt(w, env);
	ft_strcpy(w->line, "");
}

void	ft_redirect_backup(t_main *w, t_env *env)
{
	char	**coms;
	char	**cmd;
	char	*redirects;
	char	**coms_copy;
	int 	i;
	int		count;
	int		fd[2];

	i = 0;
	count = 0;
	if (ft_strchr(w->line, '>') != 0 || ft_strchr(w->line, '<') != 0) //TODO: change back to &&
	{
		if (ft_first_occur(w->line, '>', '<') == 1)
		{
			while (w->line[i])
			{
				if (w->line[i] == '>')
					count++;
				i++;
			}
			cmd = (char **)malloc(sizeof(char *) * (count + 1));
			redirects = (char *)malloc(sizeof(char *) * (count));
			cmd = get_commands(w->line, cmd, redirects);
			i = 0;
			coms = ft_strsplit(w->line, '>');
//			coms = ft_strsplit(w->line, '<');
			//TODO: Check for ';' and '|'
			while (cmd[i])
			{
				if (coms[i + 1])
				{
//					fd[0] = open(ft_strtrim(cmd[i + 1]), O_RDWR | O_CREAT, 0666);
//					if (fd[0])
						redirect_stdin(ft_strtrim(cmd[i + 1]), w, env, ft_strtrim(cmd[i]));
				}
				i++;
			}
		}
//		else if (ft_first_occur(w->line, '>', '<') == 2)
//			coms_copy = ft_strarr_append(coms);

	}
}

void	redirect_stdin(char *file, t_main *w, t_env *env, char *cmd)
{
	int		temp_fd;
	int 	test;
	int		fd;


	fd = open(file, O_RDWR | O_CREAT, 0666);
	ft_putstr("fd: ");
	ft_putnbr(fd);
	ft_putendl(";");
	ft_putstr("cmd: ");
	ft_putendl(cmd);
	ft_putendl(w->line);
	temp_fd = dup(STDIN_FILENO);
	test = dup2(fd, STDIN_FILENO);
	close(fd);
	ft_strcpy(w->line, cmd);
	ft_minishell(env, w);
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	ft_putstr("dup2 fd: ");
	ft_putnbr(test);
	ft_putendl(";");
}

void	redirect_stdout(int fd, t_main *w, t_env *env)
{
	int 	temp_fd;

	temp_fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_minishell(env, w);
	dup2(temp_fd, STDOUT_FILENO);
	close(temp_fd);
}

static	void	test(int fd[], t_main *w, t_env *env, char **coms)
{
	fd[1] = dup(STDOUT_FILENO);
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	ft_strcpy(w->line, ft_strtrim(coms[0]));
	ft_minishell(env, w);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	redirection_gt(t_main *w, t_env *env, int append)
{
	int		fd[2];
	char	**coms;

	coms = ft_strsplit(w->line, '>');
	coms[1] = ft_strtrim(coms[1]);
	if (append == 1)
		fd[0] = open(ft_strtrim(coms[1]), O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fd[0] = open(ft_strtrim(coms[1]), O_RDWR | O_CREAT, 0666);
	if (fd[0] < 0)
	{
		ft_strcpy(w->line, " ");
		ft_minishell(env, w);
	}
	else
	{
		
//		test(fd, w, env, coms);
		fd[1] = dup(STDOUT_FILENO);
		dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		ft_strcpy(w->line, ft_strtrim(coms[0]));
		ft_minishell(env, w);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	redirection_lt(t_main *w, t_env *env)
{
	char	**coms;
	int		fd[2];
	int		fd2[2];
	char	*line;
	char	*ln;
	pid_t	childpid;

	coms = ft_strsplit(w->line, '<');
	fd[0] = open(ft_strtrim(coms[1]), O_RDWR);
	ln = (char *)malloc(sizeof(char *) * 1);
	ln[0] = '\0';
	if (ft_findstr("<<", w->line))
	{
		ft_putstr("heredoc> ");
		while (get_next_line(0, &line))
		{
			if (ft_strcmp(line, ft_strtrim(coms[1])) == 0)
				break;
			ln = ft_strjoin(ln, line);
			ln = ft_strjoin(ln, "\n");
			ft_putstr(line);
			ft_putchar('\n');
			ft_putstr("heredoc> ");
		}
		ft_putstr("\33[2K\r");
		ln = ft_strjoin(ln, "\0");
		if (pipe(fd2) != -1)
		{
			childpid = fork();
			if(childpid == -1)
			{
				perror("fork");
				ft_strcpy(w->line, " ");
				ft_minishell(env, w);
			}
			else if(childpid == 0)
			{
				close(fd2[1]);
				fd[1] = dup(STDIN_FILENO);
				dup2(fd2[0], STDIN_FILENO);
				close(fd2[0]);
				ft_strcpy(w->line, coms[0]);
				ft_minishell(env, w);
				dup2(fd[1], STDIN_FILENO);
				close(fd[1]);
				close(fd2[0]);
			}
			else
			{
				close(fd2[0]);
				ft_putstr_fd(ln, fd2[1]);
				close(fd2[1]);
				wait(NULL);
				exit(0);
			}
		}
	}
	else if (fd[0] == -1)
	{
		ft_putstr("File doesn't exist or cannot be opened.\n");
		ft_strcpy(w->line, " ");
		ft_minishell(env, w);
	}
	else
	{
		w->line = ft_strnew((size_t)(ft_strlen(w->line) + 1));
		fd[1] = dup(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_strcpy(w->line, coms[0]);
		ft_minishell(env, w);
		dup2(fd[1], STDIN_FILENO);
		close(fd[1]);
	}
}
