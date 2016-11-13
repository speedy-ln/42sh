/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnkadime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:14:48 by lnkadime          #+#    #+#             */
/*   Updated: 2016/09/11 17:21:12 by lnkadime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fortytwosh.h"

static	void	parent_procc(t_redirection *r, t_main *w, t_env *env)
{
	close(r->fd2[1]);
	r->fd[1] = dup(STDIN_FILENO);
	dup2(r->fd2[0], STDIN_FILENO);
	close(r->fd2[0]);
	if (r->extras[1] == 1)
	{
		ft_doublecoms(env, w, 0);
		dup2(r->extras[2], STDIN_FILENO);
		close(r->extras[2]);
		close(r->fd2[0]);
	}
}

static	void	redirect_heredoc_supp(t_redirection *r, t_main *w, t_env *env)
{
	if (r->childpid == -1)
	{
		ft_strcpy(w->line, " ");
		ft_doublecoms(env, w, 0);
	}
	else if (r->childpid == 0)
		parent_procc(r, w, env);
	else
	{
		close(r->fd2[0]);
		ft_putstr_fd(r->ln, r->fd2[1]);
		close(r->fd2[1]);
		wait(NULL);
		exit(0);
	}
}

void			redirect_heredoc(char *file, t_main *w, t_env *env, \
		t_redirection *r)
{
//	r->fd[0] = open(ft_strtrim(file), O_RDWR);
    ft_putendl("executing heredoc...");
    ft_putendl(r->line);
    ft_putendl("r->line not initiated");
	r->ln = (char *)malloc(sizeof(char *) * 1);
	r->ln[0] = '\0';
	ft_putstr("heredoc> ");
	while (get_next_line(0, &r->line))
	{
		if (ft_strcmp(r->line, ft_strtrim(file)) == 0)
			break ;
		r->ln = ft_strjoin(r->ln, r->line);
		r->ln = ft_strjoin(r->ln, "\n");
		ft_putstr(r->line);
		ft_putchar('\n');
		ft_putstr("heredoc> ");
	}
	ft_putstr("\33[2K\r");
	r->ln = ft_strjoin(r->ln, "\0");
	if (pipe(r->fd2) != -1)
	{
		r->childpid = fork();
		redirect_heredoc_supp(r, w, env);
	}
}
