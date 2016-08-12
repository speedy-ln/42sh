/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 14:09:51 by kcowle            #+#    #+#             */
/*   Updated: 2016/07/10 14:09:59 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	char	*get_str(char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	while (ptr[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (ptr[i] != 0)
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static	char	*declare(void)
{
	char	*ptr;

	ptr = (char*)malloc(sizeof(char*) * 2);
	ptr[0] = '0';
	ptr[1] = '\0';
	return (ptr);
}

char			*ft_itoa_base(int value, int base)
{
	char		buf[50];
	char		*ptr;
	long long	num;
	int			minus;

	minus = 0;
	ptr = &buf[49];
	*ptr = '\0';
	num = value;
	if (value == 0)
		declare();
	if (value < 0)
	{
		minus = 1;
		num = num * -1;
	}
	while (num != 0)
	{
		*--ptr = "0123456789ABCDEF"[num % base];
		num /= base;
	}
	if (minus == 1)
		*--ptr = '-';
	return (get_str(ptr));
}
