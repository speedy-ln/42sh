/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/09 14:55:03 by smahomed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	select_c(char c)
{
	tputs(tgetstr("so", 0), 1, ft_ft_putchar);
	ft_putchar(c);
	tputs(tgetstr("se", 0), 1, ft_ft_putchar);
}

int		ft_init(t_main *e)
{
	t_21line_l	*tmp;
	int			x;

	if ((x = -1) && !e->a)
	{
		e->a = (t_21line_l *)malloc(sizeof(t_21line_l) * e->buffsize);
		while (++x < e->buffsize)
			e->a[x].line = 0;
	}
	if (e->y < e->buffsize && (e->buffsize += 1024 * (e->y + 1 >= e->buffsize)))
	{
		tmp = (t_21line_l *)malloc(sizeof(t_21line_l) * e->buffsize);
		while (e->a && ++x < e->buffsize && e->a[x].line)
			tmp[x] = e->a[x];
		ft_memdel((void **)&e->a);
		e->a = tmp;
	}
	e->cursor = 0;
	e->a[++e->y].x = -1;
	e->y_cursor = e->y;
	e->a[e->y].buff = 1024;
	e->a[e->y].line = (char *)malloc(sizeof(char) * e->a[e->y].buff);
	ft_strclr(e->a[e->y].line);
	ft_bzero(e->a[e->y].line, 1024);
	return (1);
}

int		ft_selectinit(t_main *env)
{
	static int	n;

	env->t.lb && (ft_cleartablines(env));
	env->t.lb = 0;
	env->t.pb = 0;
	env->t.pos = 0;
	env->t.tb = 0;
	env->t.lst = 0;
	env->t.lh = 0;
	env->t.tmplst = 0;
	env->lineprom = 0;
	env->t.ctrl_v = 0;
	if ((n += (n < 2)) && n == 1)
	{
		tcgetattr(0 * tgetent(NULL, getenv("TERM")), &env->term);
		tputs(tgetstr("ti", NULL), 1, ft_ft_putchar);
		tputs(tgetstr("ho", NULL), 1, ft_ft_putchar);
	}
	env->term.c_lflag &= ~(ECHO | ICANON);
	env->term.c_cc[VMIN] = 1;
	env->term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &env->term);
	env->lineprom = 0;
	tputs(tgetstr("vi", NULL), 1, ft_ft_putchar);
	return (1);
}

int		ft_selectend(t_main *env)
{
	env->term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &env->term);
	tputs(tgetstr("ve", NULL), 1, ft_ft_putchar);
	return (1);
}
