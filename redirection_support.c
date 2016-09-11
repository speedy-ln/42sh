/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_support.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnkadime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 14:22:33 by lnkadime          #+#    #+#             */
/*   Updated: 2016/09/11 17:28:15 by lnkadime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void			initialize_null(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = '\0';
}

static	void	get_commands_support(t_redirection *r)
{
	if (r->line[r->count + 1] && r->line[r->count + 1] == '<')
	{
		r->count++;
		r->redirects[r->redirects_count] = '1';
	}
	else
		r->redirects[r->redirects_count] = '2';
	r->temp[r->temp_count] = '\0';
	r->cmd[r->cmd_count] = (char *)malloc(sizeof(char *) * ft_strlen(r->temp));
	ft_strcpy(r->cmd[r->cmd_count], r->temp);
	r->temp_count = 0;
	r->cmd_count++;
	r->redirects_count++;
	initialize_null(r->temp);
}

static	void	get_commands_support2(t_redirection *r)
{
	if (r->line[r->count + 1] && r->line[r->count + 1] == '>')
	{
		r->count++;
		r->redirects[r->redirects_count] = '3';
	}
	else
		r->redirects[r->redirects_count] = '4';
	r->temp[r->temp_count] = '\0';
	r->cmd[r->cmd_count] = (char *)malloc(sizeof(char *) * ft_strlen(r->temp));
	ft_strcpy(r->cmd[r->cmd_count], r->temp);
	r->temp_count = 0;
	r->cmd_count++;
	r->redirects_count++;
	initialize_null(r->temp);
}

void			init_redirection(t_redirection *r)
{
	int	i;

	r->count = 0;
	r->temp_count = 0;
	r->cmd_count = 0;
	r->redirects_count = 0;
	r->temp = (char *)malloc(sizeof(char *) * (ft_strlen(r->line) + 1));
	i = -1;
	while (r->temp[++i])
		r->temp[i] = '\0';
}

char			*get_commands(t_redirection *r)
{
	init_redirection(r);
	while (r->line[r->count])
	{
		if (r->line[r->count] == '<')
			get_commands_support(r);
		else if (r->line[r->count] == '>')
			get_commands_support2(r);
		else
		{
			r->temp[r->temp_count] = r->line[r->count];
			r->temp_count++;
		}
		r->count++;
	}
	r->cmd[r->cmd_count] = ft_strdup(r->temp);
	if (r->cmd[r->cmd_count + 1])
		r->cmd[r->cmd_count + 1] = NULL;
	free(r->temp);
	return (r->redirects);
}
