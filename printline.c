/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 14:07:12 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/09 09:13:01 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

t_keyhook		*key_hook_init(t_keyhook *env)
{
	env->buffsize = 0;
	env->cursor = 0;
	env->buff = 1024;
	env->line = ft_strnew(1024);
	env->x = 0;
	env->start = -2;
	env->end = -2;
	env->pro = NULL;
	env->clip = NULL;
	env->ctrl_v = 0;
	env->lineprom = 0;
	env->ret = 0;
	return (env);
}

void			remove_last_char(t_keyhook *env)
{
	int			i;

	i = env->cursor;
	while (i < env->x)
	{
		env->line[i] = env->line[i + 1];
		i++;
	}
	env->line[env->x] = '\0';
}

void			remove_char(t_keyhook *env)
{
	int			i;

	i = --env->cursor;
	while (i < env->x)
	{
		env->line[i] = env->line[i + 1];
		i++;
	}
	env->line[env->x] = '\0';
}
