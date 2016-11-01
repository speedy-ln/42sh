/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 14:37:19 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/09 08:53:21 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void		exclamation_history(t_env *env, t_main *w)
{
	int		x;
	int		num;

	w->line++;
	num = ft_atoi(w->line);
	x = 0;
	while (x <= w->y)
	{
		if (x + 1 == num)
		{
			w->line = w->a[x].line;
			ft_putstr(w->line);
			ft_putchar('\n');
			ft_doublecoms(env, w, 0);
		}
		x++;
	}
}

void		ft_history(t_main *w)
{
	int		x;

	x = 0;
	while (x < w->y)
	{
		ft_putstr("\t");
		ft_putnbr(x + 1);
		ft_putstr("\t");
		ft_putstr(w->a[x].line);
		ft_putchar('\n');
		x++;
	}
}

void		ft_pp(t_env *env, t_main *w)
{
	int		i;
	char	**line2;
	char	*temp;

	i = 0;
	temp = ft_strtrim(w->line);
	free(w->line);
	w->line = (char *)malloc(sizeof(char *) * ft_strlen(temp) + 1);
	ft_strcpy(w->line, temp);
	free(temp);
	line2 = ft_strsplit(w->line, '|');
	while (line2[i] != NULL)
	{
		free(w->line);
		w->line = ft_strdup(line2[i]);
		ft_minishell(env, w);
		if (WIFEXITED(env->father) == 0)
			i++;
		else
			break ;
	}
	ft_free2d(line2);
}

void		ft_aa(t_env *env, t_main *w)
{
	int		i;
	char	**line2;
	char	*temp;

	i = 0;
	temp = ft_strtrim(w->line);
	free(w->line);
	w->line = (char *)malloc(sizeof(char *) * ft_strlen(temp) + 1);
	ft_strcpy(w->line, temp);
	free(temp);
	line2 = ft_strsplit(w->line, '&');
	while (line2[i] != NULL)
	{
		free(w->line);
		w->line = ft_strdup(line2[i]);
		ft_minishell(env, w);
		if (WIFEXITED(env->father) != 0)
			i++;
		else
			break ;
	}
	ft_free2d(line2);
}

void		semicolon(t_main *w, t_env *env, char **coms)
{
	int	i;

	i = 0;
	coms = ft_strsplit(w->line, ';');
	free(w->line);
	w->line = NULL;
	while (coms[i] != NULL)
	{
		w->line = ft_strtrim(coms[i]);
		ft_doublecoms(env, w, 0);
		i++;
	}
	ft_free2d(coms);
}
