/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifindstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 08:11:22 by kcowle            #+#    #+#             */
/*   Updated: 2016/08/22 10:37:06 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_ifindstr(char *str, char *find)
{
	int     in_word;
	int     i;
	int     j;
	int     find_len;

	i = 0;
	j = 0;
	find_len = ft_strlen(find);
	in_word = 0;
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
