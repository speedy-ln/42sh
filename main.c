/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/11 12:19:51 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int		main(void)
{
	t_env			*env;
	extern char		**environ;
	int				i;
	int				n;
	t_main			*w;

	i = ft_strlen2d(environ);
	w = ft_keep_main();
	env = ft_keep_struct();
	env->fail = 0;
	struct_init(env, i + 0 * (n = -1));
	w->pro = (char *)malloc(sizeof(char *) * ft_strlen("<<^>>: "));
	ft_strcpy(w->pro, "<<^>>: ");
	w->ret = '\n';
	while (++n < i)
	{
		env->enviro[n] = ft_strdup(environ[n]);
		env->envirobk[n] = ft_strdup(environ[n]);
	}
	main_init(w);
	signal(SIGINT, sinno);
	ft_doublecoms(env, w, 1);
	return (0);
}
