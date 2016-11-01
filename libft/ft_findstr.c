/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:01:11 by kcowle            #+#    #+#             */
/*   Updated: 2016/08/07 16:01:20 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_findstr(char *find, char *str)
{
	int		i;
	int		j;
	int		find_len;

	i = 0;
	j = 0;
	find_len = ft_strlen(find);
	while (str[i])
	{
		if (str[i] == find[j] && (j + 1 == find_len))
			return (1);
		else if (str[i] != find[j])
			j = 0;
		else
			j++;
		i++;
	}
	return (0);
}
