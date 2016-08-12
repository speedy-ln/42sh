/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/12 07:30:51 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	init_echo(char *line, t_echo *ec)
{
	ec->state = 0;
	ec->state2 = 0;
	ec->state = 1;
	ec->e = 0;
	ec->o = 0;
	ec->i = 0;
	ec->newline = 0;
	ec->line2 = ft_strsplit(line, ' ');
	ec->newline = ft_handle1(line, ec->line2, &ec->e, &ec->o);
}

void	ft_handle3(t_echo *ec, char *line)
{
	while (ec->state == 1)
	{
		while (line[ec->i] != '\0')
		{
			ft_handle2(line, ec);
			ec->i++;
		}
		if (ec->newline == 0)
			ft_putchar('\n');
		if (ec->state == 1 || ec->state2 == 1)
			break ;
	}
}

int		ft_handle1(char *line, char **line2, int *e, int *o)
{
	int	newline;
	int	i;

	i = 0;
	newline = 0;
	while (line2[i] != NULL)
	{
		if (ft_strncmp(line2[i], "-n", 2) == 0)
		{
			newline = 1;
			ft_strcpy(line, line + 3);
		}
		else if (ft_strncmp(line2[i], "-E", 2) == 0)
		{
			*e = 1;
			ft_strcpy(line, line + 3);
		}
		else if (ft_strncmp(line2[i], "-e", 2) == 0)
		{
			*o = 1;
			ft_strcpy(line, line + 3);
		}
		i++;
	}
	return (newline);
}

void	ft_handle2(char *line, t_echo *ec)
{
	if (line[ec->i] == '\\')
	{
		ec->i++;
		if (line[ec->i] == '0' && ec->o == 1)
			ft_printoct(line, &ec->i);
		else
			ft_putchar(line[ec->i]);
	}
	else if ((line[ec->i] != '\"' || ec->state2 == 1) \
			&& (line[ec->i] != '\'' || ec->state == 1))
		ft_putchar(line[ec->i]);
	else if (line[ec->i] == '\"')
	{
		if (ec->state == 0)
			ec->state = 1;
		else
			ec->state = 0;
	}
	else
	{
		if (ec->state2 == 0)
			ec->state2 = 1;
		else
			ec->state2 = 0;
	}
}
