/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:01:13 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/06 07:05:27 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	char	*new;

	start = 0;
	new = NULL;
	end = ft_strlen(s);
	if (s != NULL)
	{
		while (ft_iswhitespace(s[start]))
			start++;
		while (ft_iswhitespace(s[end - 1]))
			end--;
		if (end < start)
			end = start;
		new = ft_strnew(end - start);
		if (new == NULL)
			return (NULL);
		return (ft_strncpy(new, s + start, end - start));
	}
	return (new);
}
