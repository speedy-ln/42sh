/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_support3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smahomed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:51:18 by smahomed          #+#    #+#             */
/*   Updated: 2016/09/09 14:51:31 by smahomed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

int		is_tab_auto_complete0(t_main *e)
{
	if (e->t.pos && e->t.pos->next != NULL)
		e->t.pos = e->t.pos->next;
	else
		e->t.pos = e->t.lst;
	return (0);
}

int		is_tab_auto_fill0(t_main *e)
{
	e->t.h = 0;
	e->t.w = 0;
	e->t.tmplst = 0;
	if (is_tab_auto_fill1(e) == -1)
		return (0);
	if (e->t.rc == 1 && ((e->t.rc = 0) || 1))
	{
		e->t.tdir = e->t.dir;
		if (is_tab_auto_fill1(e + 0 * ((e->t.dir = ft_strdup("/bin/")) || 1))
				== -1)
		{
			free(e->t.tdir);
			return (0);
		}
	}
	return (1);
}
