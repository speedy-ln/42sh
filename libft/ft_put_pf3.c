/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pf3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:01:11 by kcowle            #+#    #+#             */
/*   Updated: 2016/08/07 16:01:21 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbrl_pf(va_list ap, const char *format, int *i)
{
	long	nb;

	*i += 1;
	if (format[*i] == 'l')
		return (ft_putnbrll_pf(ap, format, i));
	nb = va_arg(ap, long);
	return (ft_putnbr_base(nb, "0123456789"));
}

int		ft_putnbrll_pf(va_list ap, const char *format, int *i)
{
	long long	nb;

	*i += 1;
	nb = va_arg(ap, long long);
	if (format[*i] == 'd')
		*i += 0;
	return (ft_putnbr_base(nb, "0123456789"));
}

int		sft_putwchar(wchar_t *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}
