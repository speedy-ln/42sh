/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/22 15:54:23 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	minishell2_support(t_main *m)
{
	int	i;
	int	n;
	int	w;

	if (m->line2[0][0] == '/')
	{
		i = 0;
		n = 1;
		w = n;
		while (m->line2[0][n] != '/')
		{
			m->line2[0][i] = m->line2[0][n];
			while (m->line2[0][w] != '\0')
				m->line2[0][n++] = m->line2[0][w++];
			m->line2[0][n] = '\0';
			n = 0;
			w = 1;
		}
		while (m->line2[0][w] != '\0')
			m->line2[0][n++] = m->line2[0][w++];
		m->line2[0][n] = '\0';
	}
}

void	ft_minishell2(t_env *env, t_main m)
{
	if (m.line[0] != '\0')
	{
		if (m.line[0] == '.' && m.line[1] == '/')
			m.line = ft_strfcut(m.line, 2);
		if (ft_isbuiltin(env, &m) == 0)
		{
			m.comcount = 0;
			m.line = ft_strtrim(m.line);
			m.line2 = ft_strsplit(m.line, ' ');
			while (m.line2[m.comcount] != NULL)
				m.comcount++;
			*env = get_dir(env, m.line2);
			minishell2_support(&m);
			*env = ft_excecute(m.line2, m.comcount, env);
		}
	}
}

int		count_char(char *str, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	ft_pipes(t_env *env, char **coms, int i, t_main *w)
{
	char **com;

	com = ft_strsplit(coms[i], '|');
	ft_excve(env, com, count_char(coms[i], '|'), w);
	ft_free2d(com);
}
