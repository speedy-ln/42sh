/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:01:13 by kcowle            #+#    #+#             */
/*   Updated: 2016/08/07 16:01:23 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrw(char *str)
{
	int		start;
	int		end;
	char	*ptr;
	int		i;

	i = 0;
	end = ft_strlen(str);
	start = 0;
	while (str[start] == ' ')
		++start;
	while (str[end] == ' ')
		--end;
	ptr = (char *)malloc(sizeof(char *) * end - start + 1);
	while (str[start] != '\0')
	{
		ptr[i] = str[i];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
