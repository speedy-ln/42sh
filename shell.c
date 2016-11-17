/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/09 11:39:45 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	minishell_support1(t_main *m, t_env *env, char *temp)
{
	if (env->father == 0)
	{
		temp = ft_strtrim(m->line);
		free(m->line);
		m->line = temp;
		m->line2 = ft_strsplit(m->line, ' ');
		while (m->line2[m->comcount] != NULL)
			m->comcount++;
		if (m->line2[0][0] != '/')
			*env = get_dir(env, m->line2);
		*env = ft_excecute(m->line2, m->comcount, env);
	}
	else
	{
		wait(NULL);
		wait(NULL);
		env->father = 0;
	}
	if(m->line2 != NULL)
	{

	}
	if (m->line != NULL)
	{
		free(m->line);
		m->line = NULL;
	}
}

void	ft_minishell(t_env *env, t_main *m)
{
	char *temp;

	if (m->line[0] != '\0')
	{
		if (m->line[0] == '.' && m->line[1] == '/')
			m->line = ft_strfcut(m->line, 2);
		if (ft_isbuiltin(env, m) == 0)
		{
			m->comcount = 0;
			env = ft_keep_struct(*env, 0);
			m = ft_keep_main(*m, 0);
			env->father = fork();
			if (env->father >= 0)
			{
				signal(SIGINT, sinno);
				minishell_support1(m, env, temp);
			}
		}
	}
}
