/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste_key_hook.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 08:19:13 by knage             #+#    #+#             */
/*   Updated: 2016/09/06 13:57:20 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	copy(t_keyhook *env)
{
	if (env->start != -2)
	{
		if (env->start > env->end)
			env->clip = ft_strsub(env->line,
					env->end + 1, env->start);
		if (env->end > env->start)
			env->clip = ft_strsub(env->line,
					env->start + 1, env->end);
		env->start = -2;
		printline(env);
	}
}

void	paste(t_keyhook *env)
{
	char	*temp1;
	char	*temp2;

	if (env->clip)
	{
		temp1 = ft_strjoin(ft_strsub(env->line, 0,
					env->cursor), env->clip);
		temp2 = ft_strsub(env->line, env->cursor,
				ft_strlen(env->line));
		env->x = ft_strlen(env->line) +
			ft_strlen(env->clip) - 1;
		env->line = ft_strmerge(temp1, temp2);
		env->cursor += ft_strlen(env->clip);
		printline(env);
	}
}

void	ft_rev_cut(t_keyhook *env)
{
	char	*temp1;
	char	*temp2;

	env->clip = ft_strsub(env->line, env->end
			+ 1, env->start);
	env->x = ft_strlen(env->line) -
		ft_strlen(env->clip) - 1;
	temp1 = ft_strsub(env->line, 0, env->end + 1);
	temp2 = ft_strsub(env->line, env->start,
			ft_strlen(env->line));
	env->line = ft_strmerge(temp1, temp2);
}

void	ft_fwd_cut(t_keyhook *env)
{
	char	*temp1;
	char	*temp2;

	env->clip = ft_strsub(env->line, env->start
			+ 1, env->end);
	env->x = ft_strlen(env->line)
		- ft_strlen(env->clip) - 1;
	temp1 = ft_strsub(env->line, 0, env->start + 1);
	temp2 = ft_strsub(env->line, env->end,
			ft_strlen(env->line));
	env->line = ft_strmerge(temp1, temp2);
}

void	cut(t_keyhook *env)
{
	if (env->start != -2)
	{
		if (env->start > env->end)
			ft_rev_cut(env);
		if (env->end > env->start)
			ft_fwd_cut(env);
		env->start = -2;
		printline(env);
	}
}
