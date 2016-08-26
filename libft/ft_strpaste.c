/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpaste.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 09:00:26 by knage             #+#    #+#             */
/*   Updated: 2016/08/19 09:01:31 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strpaste(char *str, int start, char *clip, int end)
{
	char    *begin;
	char    *rest;
	char    *ret;

	begin = ft_strsub(str, 0, start);
	rest = ft_strsub(str, end, ft_strlen(str) - end);
	ret = ft_strjoin(begin, clip);
	ret = ft_strjoin(ret, rest);
	free(begin);
	free(rest);
	return (ret);
}
