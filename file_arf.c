/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_arf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/12 07:30:51 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	ft_links(char *line)
{
	if (ft_isdigit(line[0]) && line[1] == '>' &&
			line[2] == '&' && ft_isdigit(line[3]))
	{
		dup2(ft_atoi(&line[3]), ft_atoi(&line[0]));
		close(ft_atoi(&line[3]));
	}
	else if (ft_isdigit(line[0]) && line[1] == '>' &&
			line[2] == '&' && line[3] == '-')
		close(ft_atoi(&line[0]));
}
