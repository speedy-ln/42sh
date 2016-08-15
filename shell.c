/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/15 11:22:27 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	minishell_support1(t_main *m, t_env *env)
{
	char *line;

	line = NULL;
	ft_printf("start %i\n", env->father);
	if (env->father == 0)
	{
		ft_printf("minishell_spport1\n");
		if (ft_strcmp(m->line, "exit") == 0)
			ft_exit(env, m);
		m->line = ft_strtrim(m->line);
		m->line2 = ft_strsplit(m->line, ' ');
		while (m->line2[m->comcount] != NULL)
			m->comcount++;
		*env = get_dir(env, m->line2);
		line = ft_strtrim(m->line2[0]);
		free(m->line2[0]);
		m->line2[0] = line;
		*env = ft_excecute(m->line2, m->comcount, env);
		free(line);
	}
	else
	{
		ft_printf("wait\n");
		wait(NULL);
		wait(NULL);
	}
}

void	ft_minishell(t_env *env, t_main *m)
{
	if (m->line[0] != '\0')
	{
		if (m->line[0] == '.' && m->line[1] == '/')
			m->line = ft_strfcut(m->line, 2);
		if (ft_isbuiltin(env, m->line))
		{
			m->comcount = 0;
			env->father = fork();
			env = ft_keep_struct(*env, 0);
			m = ft_keep_main(*m, 0);
			if (env->father >= 0)
			{
				ft_printf("ft_minishell\n");
		//		signal(SIGINT, sinno);
				minishell_support1(m, env);
			}
		}
	}
}
