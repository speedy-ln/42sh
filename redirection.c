/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/11 17:35:45 by lnkadime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

static	void	init_redirect_supp2(t_redirection *r, t_main *w)
{
	r->extras[1] = 0;
	r->fd_backup[0] = dup(STDIN_FILENO);
	r->fd_backup[1] = dup(STDOUT_FILENO);
	r->count = get_redirection_count(w->line);
	r->wline_copy = (char *)malloc(sizeof(char *) * (ft_strlen(w->line) + 1));
	ft_strcpy(r->wline_copy, w->line);
	r->cmd = (char **)malloc(sizeof(char *) * (r->count + 1));
	r->redirects = (char *)malloc(sizeof(char *) * (r->count));
}

static	void	redirect_supp(t_redirection *r, t_main *w, t_env *env)
{
	r->i = 0;
	r->extras[1] = 1;
	r->count = get_redirection_count(w->line);
	r->wline_copy = (char *)malloc(sizeof(char *) * (ft_strlen(w->line) + 1));
	ft_strcpy(r->wline_copy, w->line);
	r->cmd = (char **)malloc(sizeof(char *) * (r->count + 1));
	r->redirects = (char *)malloc(sizeof(char *) * (r->count));
	r->redirects = get_commands(r);
	while (r->cmd[r->i])
	{
		ft_strcpy(w->line, r->cmd[0]);
		r->extras[0] = append_redirect(r->wline_copy, r->i + 1);
		if (r->coms[r->i + 1])
		{
			if (r->redirects[r->i] == '3' || r->redirects[r->i] == '4')
				redirect_stdout(ft_strtrim(r->cmd[r->i + 1]), w, env,\
						r->extras);
			else if (r->redirects[r->i] == '2')
				redirect_stdin(ft_strtrim(r->cmd[r->i + 1]), w, env,\
						r->extras);
			else if (r->redirects[r->i] == '1')
				redirect_heredoc(r->cmd[r->i + 1], w, env, r);
		}
		r->i++;
	}
}

static	void	redirect_supp2(t_redirection *r, t_main *w, t_env *env)
{
	init_redirect_supp2(r, w);
	r->redirects = get_commands(r);
	while (r->cmd[r->i])
	{
		ft_strcpy(w->line, r->cmd[0]);
		r->extras[0] = append_redirect(r->wline_copy, r->i);
		if (r->coms[r->i + 1])
		{
			if (r->redirects[r->i] == '3' || r->redirects[r->i] == '4')
				redirect_stdout(ft_strtrim(r->cmd[r->i + 1]), w, env, \
						r->extras);
			else if (r->redirects[r->i] == '2')
				redirect_stdin(ft_strtrim(r->cmd[r->i + 1]), w, env, \
						r->extras);
			else if (r->redirects[r->i] == '1')
				redirect_heredoc(r->cmd[r->i + 1], w, env, r);
		}
		r->i++;
	}
	ft_doublecoms(env, w, 0);
}

void			ft_redirect(t_main *w, t_env *env)
{
	t_redirection	r;

	r.i = 0;
	if ((ft_strchr(w->line, '>') != 0 || ft_strchr(w->line, '<') != 0) &&
			((ft_strchr(w->line, '>') != 0 && ft_strchr(w->line, '<') == 0) ||
			(ft_strchr(w->line, '>') == 0 && ft_strchr(w->line, '<') != 0)))
	{
		if (ft_first_occur(w->line, '>', '<') == 1)
			r.coms = ft_strsplit(w->line, '>');
		else
			r.coms = ft_strsplit(w->line, '<');
		redirect_supp(&r, w, env);
	}
	else if (ft_strchr(w->line, '>') != 0 && ft_strchr(w->line, '<') != 0)
	{
		if (ft_first_occur(w->line, '>', '<') == 1)
			r.coms = ft_strarr_append(ft_strsplit(w->line, '>'), \
					ft_strsplit(w->line, '<'));
		else
			r.coms = ft_strarr_append(ft_strsplit(w->line, '<'), \
					ft_strsplit(w->line, '>'));
		redirect_supp2(&r, w, env);
		fd_restore(r.fd_backup[0], STDIN_FILENO);
		fd_restore(r.fd_backup[1], STDOUT_FILENO);
	}
}
