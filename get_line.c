/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 11:42:14 by knage             #+#    #+#             */
/*   Updated: 2016/11/15 12:08:27 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	cursor_movement(char *buff, t_keyhook *env)
{
	if (ft_isprint(buff[0]) && env->x >= env->buff)
		malloc_buff(env);
	else if (buff[0] == 127 && env->x > -1 && env->cursor > 0)
	{
		remove_char(env);
		--env->x;
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 67 && buff[3] == 0)
	{
		env->start = -2;
		if (env->cursor < env->x)
			env->cursor += 1;
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68 && buff[3] == 0)
	{
		env->start = -2;
		if (env->cursor > 0)
			env->cursor -= 1;
	}
}

void	check_line(t_keyhook *env, char *temp)
{
	env->cursor = -2;
	printline(env);
	temp = ft_strdup(env->line);
	free(env->line);
	env->line = ft_strtrim(temp);
	free(temp);
	env->line = variable_check(env->line);
	env->line[env->x + 2] = '\0';
}

int		return_line(char *buff, t_keyhook *env)
{
	char		*temp;

	if (buff[0] == env->ret[0] && !buff[1] && env->type == 1)
	{
		check_line(env, temp);
		return (1);
	}
	else if (ft_strcmp(env->line, env->ret) == 0)
	{
		check_line(env, temp);
		return (1);
	}
	return (0);
}

int		handle_new_line(char *buff, t_keyhook *env)
{
	char		*temp;
	char		*temp2;

	if (buff[0] == '\n')
	{
		buff[0] = '\n';
		buff[1] = '\0';
		env->cursor = -3;
		printline(env);
		ft_putchar('\n');
		temp2 = ft_strjoin(env->line, buff);
		temp = get_str(env->pro, env->ret, env->type);
		free(env->line);
		env->line = ft_strjoin(temp2, temp);
		env->line = variable_check(env->line);
		return (1);
	}
	return (0);
}

char	*get_str(char *promt, char *ret, int type)
{
	char		buff[8];
	t_keyhook	env;

	key_hook_init(&env);
	env.pro = promt;
	env.ret = ret;
	env.type = type;
	while (1)
	{
		ft_bzero(buff, 8);
		printline(&env);
		read(0, buff, 8);
		cursor_movement(buff, &env);
		if (return_line(buff, &env) == 1)
			return (env.line);
		if (handle_new_line(buff, &env) == 1)
			return (env.line);
		ctrl_v(&env, buff);
	}
	return (get_str(promt, ret, env.type));
}
