/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 09:20:44 by knage             #+#    #+#             */
/*   Updated: 2016/09/10 13:48:23 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

char	*print_var(t_env *env, char *line, int start, int i)
{
	char	*ret;
	char	*temp;
	int		size;

	size = 1;
	while (line[i] != '\0' && line[i] != ' ' && \
			line[i] != '`' && line[i] != '"')
	{
		size++;
		i++;
	}
	if (start != 0)
	{
		temp = ft_strsub(line, start, size);
		ret = ft_getvar(env, temp);
		if (ret != NULL)
		{
			free(temp);
			temp = ft_strpaste(line, start - 1, ret, i);
			free(line);
			line = temp;
			free(ret);
		}
	}
	return (line);
}

char	*is_var(char *line, t_env *env)
{
	int	i;
	int	start;

	i = 0;
	if (line != NULL)
	{
		while (line[i])
		{
			if (line[i] == '$')
			{
				i++;
				start = i;
				line = print_var(env, line, start, i);
				i = start - 1;
			}
			i++;
		}
	}
	return (line);
}
