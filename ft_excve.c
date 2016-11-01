/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/18 09:39:23 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_execve1(t_execve *c, t_env *env, char **com, t_main *w)
{
	while (com[++c->y + 1] != NULL)
	{
		c->length = c->x;
		env->father = fork();
		env = ft_keep_struct(*env, 0);
		w = ft_keep_main(*w, 0);
		if (env->father >= 0)
		{
			signal(SIGINT, sinno);
			if (env->father == 0)
			{
				c->length = c->x;
				dup2(c->fd[c->n], STDIN);
				dup2(c->fd[c->n + 3], STDOUT);
				while (c->length >= 0)
					close(c->fd[--c->length + 1]);
				w->line = com[c->y];
				ft_minishell2(env, *w);
				exit(0);
			}
		}
		else
			ft_putstr("FORK");
		c->n = c->n + 2;
	}
}

void	ft_execve2(t_execve *c, t_env *env, char **com, t_main *w)
{
	c->n = 0;
	ft_execve1(c, env, com, w);
	env = ft_keep_struct(*env, 0);
	w = ft_keep_main(*w, 0);
	if (((env->father = fork()) || 1) && env->father >= 0)
	{
		signal(SIGINT, sinno);
		if (env->father == 0 && ((c->length = c->x) || 1))
		{
			dup2(c->fd[c->n], STDIN);
			while (c->length >= 0)
				close(c->fd[--c->length + 1]);
			w->line = com[c->y];
			ft_minishell2(env, *w);
			exit(0);
		}
	}
	else
		ft_putstr("FORK");
	c->length = c->x;
	while (((c->k = 0) || 1) && c->length >= 0)
		close(c->fd[--c->length + 1]);
	while (c->k <= c->i)
		c->k += 1 + (env->father = 0) + 0 * wait(NULL);
}

void	ft_excve(t_env *env, char **com, int i, t_main *w)
{
	int			fd[(i * 2)];
	t_execve	c;

	c.u = 0;
	c.length = 0;
	c.x = 0;
	c.y = 0;
	c.fd = fd;
	while (((c.i = i) || 1) && c.x <= (i * 2))
		c.x = c.x + 2 + 0 * pipe(c.fd + c.x);
	c.x = (c.x - 2);
	c.length = c.x;
	env = ft_keep_struct(*env, 0);
	w = ft_keep_main(*w, 0);
	if (((env->father = fork()) || 1) && env->father >= 0)
		if (((signal(SIGINT, sinno)) || 1) && env->father == 0)
		{
			dup2(fd[1], STDOUT);
			while (c.length >= 0)
				close(c.fd[--c.length + 1]);
			w->line = com[0];
			ft_minishell2(env, *w);
			exit(0);
		}
	ft_execve2(&c, env, com, w);
}
