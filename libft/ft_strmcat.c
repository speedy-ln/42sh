/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 12:39:37 by kcowle            #+#    #+#             */
/*   Updated: 2016/07/21 12:44:01 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strmcat(char *str, char *str2)
{
	char *ptr;
	int i;
	int mid;
	
	mid = 0;
	i = 0;
	ptr = (char *)malloc(sizeof(char *) * ft_strlen(str) + ft_strlen(str2) + 1);
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	while (str2[mid] != '\0')
	{
		ptr[i] = str2[mid];
		i++;
		mid++;
	}
	ptr[i] = '\0';
	return (ptr);
}
