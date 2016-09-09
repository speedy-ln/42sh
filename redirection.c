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

void	ft_redirect_backup(t_main *w, t_env *env)
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

static	int	get_redirection_count(char *line)
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

static	int append_redirect(char *line, int iteration)
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

void	ft_redirect(t_main *w, t_env *env)
{
	char	**coms;
	char	**cmd;
	char	*redirects;
	char	*wline_copy;
	int 	i;
	int		count;
	int		extras[4];
	int		fd_backup[2];
//	int 	append;

	i = 0;
	if ((ft_strchr(w->line, '>') != 0 || ft_strchr(w->line, '<') != 0) &&
			( (ft_strchr(w->line, '>') !=0 && ft_strchr(w->line, '<') == 0) ||
			  (ft_strchr(w->line, '>') == 0 && ft_strchr(w->line, '<') != 0))
			)
	{
		if (ft_first_occur(w->line, '>', '<') == 1)
			coms = ft_strsplit(w->line, '>');
		else
			coms = ft_strsplit(w->line, '<');
		extras[1] = 1;
		count = get_redirection_count(w->line);
		wline_copy = (char *)malloc(sizeof(char *) * (ft_strlen(w->line) + 1));
		ft_strcpy(wline_copy, w->line);
		cmd = (char **)malloc(sizeof(char *) * (count + 1));
		redirects = (char *)malloc(sizeof(char *) * (count));
		cmd = get_commands(w->line, cmd, redirects);
		//TODO: Check for ';' and '|'
		while (cmd[i])
		{
			ft_strcpy(w->line, cmd[0]);
			extras[0] = append_redirect(wline_copy, i + 1);
			if (coms[i + 1])
			{
				if (redirects[i] == '3' || redirects[i] == '4')
					redirect_stdout(ft_strtrim(cmd[i + 1]), w, env, extras);
				else if (redirects[i] == '2')
					redirect_stdin(ft_strtrim(cmd[i + 1]), w, env, extras);
				else if (redirects[i] == '1')
					redirect_heredoc(cmd[i + 1], w, env);
			}
			i++;
		}
	}
	else if (ft_strchr(w->line, '>') != 0 && ft_strchr(w->line, '<') != 0)
	{
		if (ft_first_occur(w->line, '>', '<') == 1)
			coms = ft_strarr_append(ft_strsplit(w->line, '>'), ft_strsplit(w->line, '<'));
		else
			coms = ft_strarr_append(ft_strsplit(w->line, '>'), ft_strsplit(w->line, '<'));
		extras[1] = 0;
		fd_backup[0] = dup(STDIN_FILENO);
		fd_backup[1] = dup(STDOUT_FILENO);
		count = get_redirection_count(w->line);
		wline_copy = (char *)malloc(sizeof(char *) * (ft_strlen(w->line) + 1));
		ft_strcpy(wline_copy, w->line);
		cmd = (char **)malloc(sizeof(char *) * (count + 1));
		redirects = (char *)malloc(sizeof(char *) * (count));
		cmd = get_commands(w->line, cmd, redirects);
		while (cmd[i])
		{
			ft_strcpy(w->line, cmd[0]);
			extras[0] = append_redirect(wline_copy, i + 1);
			if (coms[i + 1])
			{
				if (redirects[i] == '3' || redirects[i] == '4')
				{//TODO: Modify
					redirect_stdout(ft_strtrim(cmd[i + 1]), w, env, extras);
				}
				else if (redirects[i] == '2')
				{
					redirect_stdin(ft_strtrim(cmd[i + 1]), w, env, extras);
				}
				else if (redirects[i] == '1')
				{
					redirect_heredoc(cmd[i + 1], w, env);
				}
			}
			i++;
		}
		ft_minishell(env, w);
		fd_restore(fd_backup[0], STDIN_FILENO);
		fd_restore(fd_backup[1], STDOUT_FILENO);

	}
}

void	redirect_heredoc(char *file, t_main *w, t_env *env)
{
	char	*line;
	char	*ln;
	pid_t	childpid;
	int		fd[2];
	int		fd2[2];

	fd[0] = open(ft_strtrim(file), O_RDWR);
	ln = (char *)malloc(sizeof(char *) * 1);
	ln[0] = '\0';
	ft_putstr("heredoc> ");
	while (get_next_line(0, &line))
	{
		if (ft_strcmp(line, ft_strtrim(file)) == 0)
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

void	redirect_stdin(char *file, t_main *w, t_env *env, int extras[])
{
	int		temp_fd;
	int		fd;


	fd = open(file, O_RDWR , 0666);
	if (fd == -1)
	{
		ft_putstr("File doesn't exist or cannot be opened.\n");
		ft_strcpy(w->line, " ");
		ft_minishell(env, w);
	}
	extras[2] = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (extras[1] == 1)
	{
		ft_minishell(env, w);
		fd_restore(extras[2], STDIN_FILENO);
//		dup2(extras[2], STDOUT_FILENO);
//		close(extras[2]);
	}
//	ft_minishell(env, w);
//	dup2(temp_fd, STDIN_FILENO);
//	close(temp_fd);
}

void	redirect_stdout(char *file, t_main *w, t_env *env, int extras[])
{
//	int		temp_fd;
	int		fd;

	if (extras[0] == 1)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fd = open(file, O_RDWR | O_CREAT, 0666); //TODO: Error checking.
	extras[3] = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (extras[1] == 1)
	{
		ft_minishell(env, w);
		fd_restore(extras[3], STDOUT_FILENO);
//		dup2(extras[3], STDOUT_FILENO);
//		close(extras[3]);
	}
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
