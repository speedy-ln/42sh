/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 13:58:10 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/06 13:58:15 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	main_init(t_main *main)
{
	main->line = NULL;
	main->start = -2;
	main->clip = NULL;
	main->buffsize = 0;
	main->a = 0;
	main->y = -1;
	main->lineprom = 0;
	main->quote = 2;
	main->open = 0;
	ft_init(main);
}

void	struct_init(t_env *env, int i)
{
	env->prev_pwd = NULL;
	env->cont = 0;
	env->father = 0;
	env->vars = 0;
	env->enviro = (char **)malloc(sizeof(char **) * i + 1);
	env->envirobk = (char **)malloc(sizeof(char **) * i + 1);
}
