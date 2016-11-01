/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/09 08:54:27 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

t_main	*ft_keep_main(void)
{
	static t_main m;

	return (&m);
}

t_env	*ft_keep_struct(void)
{
	static t_env tmp;

	return (&tmp);
}

void	ft_quit(void)
{
	t_env	*env;
	t_main	*w;

	env = ft_keep_struct();
	w = ft_keep_main();
	if (env->father != 0)
		kill(env->father, SIGINT);
	else
		ft_exit(env, w);
}

void	sinno(int signall)
{
	if (signall == SIGINT)
		ft_quit();
}
