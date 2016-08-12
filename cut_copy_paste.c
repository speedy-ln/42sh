/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/12 07:30:51 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_copy(t_main *env)
{
	if (env->start != -2)
	{
		if (env->start > env->end)
			env->clip = ft_strsub(env->a[env->y].line,
					env->end + 1, env->start);
		if (env->end > env->start)
			env->clip = ft_strsub(env->a[env->y].line,
					env->start + 1, env->end);
		env->start = -2;
		ft_printstring(env);
	}
}

void	ft_paste(t_main *env)
{
	char	*temp1;
	char	*temp2;

	if (env->clip)
	{
		temp1 = ft_strjoin(ft_strsub(env->a[env->y].line, 0,
					env->cursor), env->clip);
		temp2 = ft_strsub(env->a[env->y].line, env->cursor,
				ft_strlen(env->a[env->y].line));
		env->a[env->y].x = ft_strlen(env->a[env->y].line) +
			ft_strlen(env->clip) - 1;
		env->a[env->y].line = ft_strmerge(temp1, temp2);
		env->cursor += ft_strlen(env->clip);
		ft_printstring(env);
	}
}

void	rev_cut(t_main *env)
{
	char	*temp1;
	char	*temp2;

	env->clip = ft_strsub(env->a[env->y].line, env->end
			+ 1, env->start);
	env->a[env->y].x = ft_strlen(env->a[env->y].line) -
		ft_strlen(env->clip) - 1;
	temp1 = ft_strsub(env->a[env->y].line, 0, env->end + 1);
	temp2 = ft_strsub(env->a[env->y].line, env->start,
			ft_strlen(env->a[env->y].line));
	env->a[env->y].line = ft_strmerge(temp1, temp2);
}

void	fwd_cut(t_main *env)
{
	char	*temp1;
	char	*temp2;

	env->clip = ft_strsub(env->a[env->y].line, env->start
			+ 1, env->end);
	env->a[env->y].x = ft_strlen(env->a[env->y].line)
		- ft_strlen(env->clip) - 1;
	temp1 = ft_strsub(env->a[env->y].line, 0, env->start + 1);
	temp2 = ft_strsub(env->a[env->y].line, env->end,
			ft_strlen(env->a[env->y].line));
	env->a[env->y].line = ft_strmerge(temp1, temp2);
}

void	ft_cut(t_main *env)
{
	if (env->start != -2)
	{
		if (env->start > env->end)
			rev_cut(env);
		if (env->end > env->start)
			fwd_cut(env);
		env->start = -2;
		ft_printstring(env);
	}
}
