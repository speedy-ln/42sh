/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 08:41:34 by knage             #+#    #+#             */
/*   Updated: 2016/09/07 11:44:51 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	select_char(t_keyhook *env, char buff[4])
{
	if (buff[0] == -30 && buff[1] == -119 && buff[2] == -92)
	{
		if (env->start == -2 && ((env->start = env->cursor) || 1))
			env->end = env->cursor - 1;
		env->cursor--;
		env->end--;
		if (env->start == env->end - 1 && (env->end = -2))
			env->start = -2;
	}
	else if (buff[0] == -30 && buff[1] == -119 && buff[2] == -91)
	{
		if (env->start == -2 && ((env->start = env->cursor - 1) || 1))
			env->end = env->cursor;
		env->cursor += (env->cursor != env->x);
		env->end++;
		if (env->start == env->end - 1 && (env->end = -2))
			env->start = -2;
	}
	else if (!buff[1] && (buff[0] == 32 || ft_isprint(buff[0])))
	{
		insert_char(env, buff[0]);
		if (env->cursor < env->x + 1)
			env->cursor += 1;
	}
}

int		extra_keyhooks(t_keyhook *env, char buff[4])
{
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 51 && buff[3] == 126)
	{
		if (env->x > -1 && env->cursor <= env->x)
		{
			remove_last_char(env);
			--env->x;
		}
	}
	else if (buff[0] == -30 && buff[1] == -119 && buff[2] == -120 && !buff[3])
		cut(env);
	else if (buff[0] == -61 && buff[1] == -89 && !buff[2] && !buff[3])
		copy(env);
	else if (buff[0] == -30 && buff[1] == -120 && buff[2] == -102 && !buff[3])
		paste(env);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 53
			&& buff[3] == 126 && env->x > -1)
		env->cursor = 0;
	else if (buff[0] == -30 && buff[1] == -120 && buff[2] == -111 && !buff[3])
		env->cursor = ft_ctrlup(env->cursor, env->x);
	else if (buff[0] == -61 && buff[1] == -97 && !buff[2] && !buff[3])
		env->cursor = ft_ctrldown(env->cursor, env->x);
	else
		select_char(env, buff);
	return (1);
}

int		word_jump(t_keyhook *env, char buff[4])
{
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 54 && buff[3] == 126)
		env->cursor = env->x + 1;
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 72 && !buff[3])
	{
		while (env->cursor > 0 && env->line[env->cursor - 1] == ' ')
			env->cursor -= 1;
		while (env->cursor > 0 && env->line[env->cursor - 1] != ' ')
			env->cursor -= 1;
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 70 && !buff[3])
	{
		while (env->cursor <= env->x
				&& env->line[env->cursor + 1] == ' ')
			env->cursor += 1;
		while (env->cursor <= env->x
				&& env->line[env->cursor + 1] != ' ')
			env->cursor += 1;
		env->cursor = env->cursor * (env->cursor >= env->x)\
					+ (env->cursor + 2) * (env->cursor < env->x);
	}
	else
		extra_keyhooks(env, buff);
	return (1);
}

int		ctrl_v(t_keyhook *env, char buff[4])
{
	if (buff[0] == 22 && !buff[1] && !buff[2] && !buff[3])
		env->ctrl_v = 1;
	else
		word_jump(env, buff);
	return (1);
}
