/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbcut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 14:09:51 by kcowle            #+#    #+#             */
/*   Updated: 2016/07/10 14:09:59 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strbcut(char *line, int n)
{
	char	*str;
	int		i;
	int		total;

	i = ft_strlen(line);
	total = i - n;
	str = (char *)malloc(sizeof(char *) * total + 1);
	i = 0;
	while (i < total)
	{
		str[i] = line[i];
		++i;
	}
	return (str);
}
