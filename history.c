/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/11 11:14:24 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

char	**ft_insert(t_env *env, char *com)
{
	int		i;
	int		k;
	char	**array;

	i = 0;
	k = 0;
	array = (char **)malloc(sizeof(char **) + 1);
	array[0] = ft_strnew(1);
	if (env->history[0] != NULL)
	{
		while (env->history[i] != NULL)
			i++;
		array = (char **)malloc(sizeof(char **) * i + 1);
		while (env->history[k] != NULL)
		{
			array[k] = (char *)malloc(sizeof(char *)
					* ft_strlen(env->history[k]));
			ft_strcpy(array[k], env->history[k]);
			k++;
		}
		array[k] = (char *)malloc(sizeof(char *) * ft_strlen(com));
		ft_strcpy(array[k], com);
	}
	return (array);
}

void	paste_history(t_21line_l *history, char *str, t_history his)
{
	char	*prev;
	char	*after;
	char	*temp;

	temp = ft_strsub(str, his.start + 1, his.i - his.start);
	his.pos = ft_atoi(temp);
	free(temp);
	his.pos -= 1;
	if (history[his.pos].line[0] != '\0')
	{
		prev = ft_strsub(str, 0, his.start);
		after = ft_strsub(str, his.i, ft_strlen(str) - his.i);
		free(str);
		str = ft_strjoin(prev, history[his.pos].line);
		str = ft_strjoin(str, after);
		free(prev);
		free(after);
		his.yes = 1;
	}
}

char	*is_history(char *str, t_21line_l *history)
{
	t_history his;

	his.i = 0;
	his.start = 0;
	his.pos = 0;
	his.yes = 0;
	if (str != NULL)
	{
		while (str[his.i])
		{
			if (str[his.i] == '!' && ft_isnbr(str[his.i + 1]))
			{
				his.start = his.i;
				his.i++;
				while (ft_isnbr(str[his.i]))
					his.i++;
				paste_history(history, str, his);
			}
			his.i++;
		}
	}
	if (his.yes == 1)
		ft_printf("\n%s\n", str);
	return (str);
}
