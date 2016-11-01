/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 09:52:47 by knage             #+#    #+#             */
/*   Updated: 2016/09/09 06:53:46 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void			insert_char(t_keyhook *env, char c)
{
	int		x;

	x = ++env->x;
	while (--x >= env->cursor)
	{
		env->line[x + 1] = env->line[x];
	}
	env->line[x + 1] = c;
}

void			malloc_buff(t_keyhook *env)
{
	char	*tmp;
	int		i;

	i = 0;
	env->buff += 1024;
	tmp = (char *)malloc(sizeof(char) * env->buff);
	while (env->line[i])
	{
		tmp[i] = env->line[i];
		i++;
	}
	if (env->line)
		free(env->line);
	env->line = tmp;
}

void			linextention(t_keyhook *env)
{
	tputs(tgetstr("dl", 0), 1, ft_ft_putchar);
	while (env->lineprom > 0 && ((env->lineprom -= 1) || 1))
	{
		tputs(tgetstr("dl", 0), 1, ft_ft_putchar);
		tputs(tgetstr("up", 0), 1, ft_ft_putchar);
		tputs(tgetstr("cr", 0), 1, ft_ft_putchar);
	}
	tputs(tgetstr("cr", 0), 1, ft_ft_putchar);
	ft_putstr(env->pro);
}

void			print_char(t_keyhook *env, int i)
{
	if (env->start != -2 && i > env->start && i < env->end)
		select_c(env->line[i]);
	else if (env->start != -2 && i < env->start && i > env->end)
		select_c(env->line[i]);
	else if (i == env->cursor)
		ft_cursor(env->line[i]);
	else
	{
		if (env->line[i] == '\t')
			write(1, "    ", 4);
		else
			ft_putchar(env->line[i]);
	}
}

void			printline(t_keyhook *env)
{
	struct winsize	win;
	int				i;
	int				t[3];

	ioctl(0 * ((t[0] = win.ws_col) || 1), TIOCGWINSZ, &win);
	i = -1;
	linextention(env);
	t[1] = 7;
	env->lineprom = 0;
	while (++i <= env->x && ((t[1] += 1) || 1))
	{
		env->lineprom += (t[1] == t[0]);
		t[1] = t[1] * (t[1] < t[0]);
		if (env->line[i])
			print_char(env, i);
	}
	if (env->cursor == env->x)
		ft_cursor(' ');
}
