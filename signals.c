/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/12 07:30:54 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

t_main	*ft_keep_main(t_main w, int i)
{
	static t_main m;

	if (i == 0)
	{
		m = w;
		return (&m);
	}
	else
		return (&m);
}

t_env	*ft_keep_struct(t_env env, int i)
{
	static t_env tmp;

	if (i == 0)
	{
		tmp = env;
		return (&tmp);
	}
	else
	{
		return (&tmp);
	}
}

void	ft_quit(void)
{
	t_env	*env;
	t_main	*w;

	env = NULL;
	w = NULL;
	env = ft_keep_struct(*env, 1);
	w = ft_keep_main(*w, 1);
	if (env->father != 0)
	{
		w->line = NULL;
		w->start = -2;
		w->clip = NULL;
		w->buffsize = 0;
		w->a = 0;
		w->y = -1;
		ft_selectinit(w);
		ft_init(w);
		kill(env->father, SIGINT);
		ft_doublecoms(env, w);
	}
	ft_exit(env, w);
}

void	sinno(int signall)
{
	if (signall == SIGINT)
		ft_quit();
}
