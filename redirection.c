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
    {
        redirection_lt(w, env);
    }
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
    t_redirection   r;

//    r = NULL;
	coms = ft_strsplit(w->line, '<');
    if (ft_findstr("<<", w->line))
    {
        r.line = ft_strnew((size_t) (ft_strlen(w->line) + 1));
//        ft_putendl(r.line);
//        r.line = (char*)malloc((sizeof(char *)) * 1000);
        init_redirection(&r);
        redirect_heredoc(ft_strtrim(coms[1]), w, env, &r);
    }
    else {
        fd[0] = open(ft_strtrim(coms[1]), O_RDWR);
        if (fd[0] == -1) {
            ft_putstr("File doesn't exist or cannot be opened.\n");
            ft_strcpy(w->line, " ");
            ft_minishell(env, w);
        } else {
            w->line = ft_strnew((size_t) (ft_strlen(w->line) + 1));
            fd[1] = dup(STDIN_FILENO);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            ft_strcpy(w->line, coms[0]);
            ft_minishell(env, w);
            dup2(fd[1], STDIN_FILENO);
            close(fd[1]);
        }
    }
}
