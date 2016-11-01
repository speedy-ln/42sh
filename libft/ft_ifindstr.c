/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifindstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 08:11:22 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/10 13:45:49 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ifindstr(char *str, char *find)
{
	int	i;
	int	j;
	int	find_len;

	i = 0;
	j = 0;
	find_len = ft_strlen(find);
	while (str[i])
	{
		if (str[i] == find[j] && (j + 1 == find_len))
			return (i - j);
		else if (str[i] != find[j])
			j = 0;
		else
			j++;
		i++;
	}
	return (-1);
}
