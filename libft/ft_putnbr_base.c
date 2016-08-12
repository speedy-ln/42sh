/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:01:12 by kcowle            #+#    #+#             */
/*   Updated: 2016/08/07 16:01:21 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_base(long nb, const char *base)
{
	long			div;
	long			i;
	long			result;
	long			size_base;

	i = 0;
	size_base = ft_strlen(base);
	if (nb < 0)
	{
		ft_putchar('-');
		i++;
	}
	div = 1;
	while (ft_abs((nb / div)) >= size_base)
		div = div * size_base;
	while (div > 0)
	{
		result = ft_abs((nb / div) % size_base);
		ft_putchar(base[result]);
		div = div / size_base;
		i++;
	}
	return (i);
}

int		ft_putnbr_base_u(unsigned int nb, const char *base)
{
	int					i;
	unsigned int		div;
	unsigned int		result;
	unsigned int		size_base;

	i = 0;
	size_base = ft_strlen(base);
	div = 1;
	while ((nb / div) >= size_base)
		div = div * size_base;
	while (div > 0)
	{
		result = (nb / div) % size_base;
		ft_putchar(base[result]);
		div = div / size_base;
		i++;
	}
	return (i);
}

int		ft_return_nb_nb(long nb, const char *base)
{
	long		i;
	long		div;
	long		size_base;

	i = 0;
	size_base = ft_strlen(base);
	div = 1;
	while ((nb / div) >= size_base)
		div = div * size_base;
	while (div > 0)
	{
		div = div / size_base;
		i++;
	}
	return (i);
}

int		ft_return_nb_nb_di(int nb, const char *base)
{
	int				i;
	int				div;
	int				size_base;

	i = 0;
	if (nb < 0)
		i++;
	nb = ft_abs(nb);
	size_base = ft_strlen(base);
	div = 1;
	while ((nb / div) >= size_base)
		div = div * size_base;
	while (div > 0)
	{
		div = div / size_base;
		i++;
	}
	return (i);
}
