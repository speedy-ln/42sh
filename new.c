/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 10:52:00 by kcowle            #+#    #+#             */
/*   Updated: 2016/08/23 15:08:49 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	exclamation_history(t_env *env, t_main *w)
{
	int     x;
	int num;

	w->line++;
	num = ft_atoi(w->line);
	x = 0;
	while (x <= w->y)
	{
		if (x + 1 == num)
		{
			w->line = w->a[x].line;
			ft_putstr(w->line);
			ft_putchar('\n');
			ft_doublecoms(env, w, 0);
		}
		x++;
	}
}

void	ft_if_else(t_env *env, t_main *w)
{
	int i;
	int and;
	int or;
	char *bk;
	char **line2;

	bk = w->line;
	i = 0;
	and = ft_ifindstr(w->line, "&&");
	or = ft_ifindstr(w->line, "||");
	if (and < or)
	{
		line2 = ft_strsplit(w->line, '&');
		w->line = line2[0];
		ft_minishell(env, w);
		if (WIFEXITED(env->father) != 0)
		{
			line2 = ft_strsplit(line2[1], '|');
			w->line = line2[0];
			ft_minishell(env, w);
		}
		else
		{
			line2 = ft_strsplit(line2[1], '|');
			w->line = line2[1];
			ft_minishell(env, w);
		}
	}
	else if (and > or)
	{
		line2 = ft_strsplit(w->line, '|');
		w->line = line2[0];
		ft_minishell(env, w);
		if (WIFEXITED(env->father) == 0)
		{
			line2 = ft_strsplit(line2[1], '&');
			w->line = line2[0];
			ft_minishell(env, w);
		}
		else
		{
			line2 = ft_strsplit(line2[1], '&');
			w->line = line2[1];
			ft_minishell(env, w);
		}
	}
	ft_doublecoms(env, w, 1);
}

void	ft_history(t_main *w)
{
	int		x;

	x = 0;
	while (x < w->y)
	{
		ft_putstr("\t");
		ft_putnbr(x + 1);
		ft_putstr("\t");
		ft_putstr(w->a[x].line);
		ft_putchar('\n');
		x++;
	}
}

void	ft_pp(t_env *env, t_main *w)
{
	int i;
	char **line2;

	i = 0;
	w->line = ft_strtrim(w->line);
	line2 = ft_strsplit(w->line, '|');
	while (line2[i] != NULL)
	{
		w->line = line2[i];
		ft_minishell(env, w);
		if (WIFEXITED(env->father) == 0)
			i++;
		else
			ft_doublecoms(env, w, 1);
	}
}

void	ft_aa(t_env *env, t_main *w)
{
	int i;
	char **line2;

	i = 0;
	w->line = ft_strtrim(w->line);
	line2 = ft_strsplit(w->line, '&');
	while (line2[i] != NULL)
	{
		w->line = line2[i];
		ft_minishell(env, w);

		if (WIFEXITED(env->father) != 0)
			i++;
		else
			ft_doublecoms(env, w, 1);
	}
}

void	semicolon(t_main *w, t_env *env, char **coms)
{
	int	i;

	i = 0;
	coms = ft_strsplit(w->line, ';');
	while (coms[i] != NULL)
	{
		w->line = ft_strtrim(coms[i]);
		ft_minishell(env, w);
		i++;
	}
}

void	com_pipes(t_main *w, t_env *env, char **coms)
{
	int	i;

	i = 0;
	coms = ft_strsplit(w->line, ';');
	while (coms[i] != NULL)
	{
		if (ft_strchr(coms[i], '|') == 0)
		{
			w->line = ft_strtrim(coms[i]);
			ft_minishell(env, w);
		}
		else if (ft_strchr(coms[i], '|') != 0)
			ft_pipes(env, coms, i, w);
		i++;
	}
}

t_main *ft_bquote(t_env *env, t_main *w)
{
	int i;
	int x;
	int num;
	char *com;
	char *line;
	char *bk;
	int fd[2];
	char *str;
	char *buf;
	char *temp;

	bk = (char *)malloc(sizeof(char *) * ft_strlen(w->line) + 1);
	ft_strcpy(bk, w->line);
	buf = (char *)malloc(sizeof(char *) * 3);
	ft_bzero(buf, 2);
	num = 0;
	temp = NULL;
	str = (char *)malloc(sizeof(char *) * 2);
	ft_bzero(str, 2);
	i = ft_ifindstr(w->line, "`");
	if (i != -1)
	{
		w->line[i] = '*';
		x = ft_ifindstr(w->line, "`");
		if (x != -1)
		{
			w->line[i] = '`';
			i++;
			x--;
			bk = (char *)malloc(sizeof(char *) * ft_strlen(w->line) + 1);
			ft_strcpy(bk, w->line);
			com = (char *)malloc(sizeof(char *) * x - i + 2);
			ft_bzero(com, x - i + 2);
			while (i <= x)
			{
				com[num] = w->line[i];
				i++;
				num++;
			}
			com[num + 1] = '\0';
			pipe(fd);
			env->father = fork();
			if (env->father == 0)
			{
				dup2(fd[1], STDOUT);
				close(fd[0]);
				ft_strcpy(w->line, com);
				ft_minishell2(env, *w);
				exit(0);
			}
			else
			{
				wait(NULL);
				close(fd[1]);
				while (read(fd[0], buf, 1) != 0)
				{
					temp = (char *)malloc(sizeof(char *) * ft_strlen(str) + 2);
					ft_bzero(temp, ft_strlen(str) + 1);
					temp[ft_strlen(str) + 2] = '\0';
					if (str[0] != '\0')
						ft_strcpy(temp, str);
					ft_strcat(temp, buf);
					free(str);
					str = (char *)malloc(sizeof(char *) * ft_strlen(temp) + 2);
					ft_bzero(str, ft_strlen(temp) + 1);
					str[ft_strlen(temp) + 2] = '\0';
					ft_strcpy(str, temp);
					free(temp);
				}
				str = ft_strtrim(str);
				i = ft_ifindstr(w->line, "`");
				w->line[i] = '*';
				x = ft_ifindstr(w->line, "`");
				w->line[i] = '`';
				free(w->line);
				w->line = (char *)malloc(sizeof(char *) * ft_strlen(ft_strpaste(bk, i, str, x + 1)));
				ft_strcpy(w->line, ft_strpaste(bk, i, str, x + 1));
				if (ft_ifindstr(w->line, "`") != -1)
					w = ft_bquote(env, w);
				else
					return (w);
			}
		}
		else
		{
			w->line[i] = '`';
			free(w->pro);
			w->pro = (char *)malloc(sizeof(char *) * ft_strlen("bquote> "));
			ft_strcpy(w->pro, "bquote> ");
			w->ret = '`';
			ft_selectinit(w);
			while (ft_select(w, &str))
				;
			ft_selectend(w);
			free(w->pro);
			w->pro = (char *)malloc(sizeof(char *) * ft_strlen("<<^>>: "));
			ft_strcpy(w->pro, "<<^>>: ");
			w->ret = '\n';
			temp = (char *)malloc(sizeof(char *) * ft_strlen(bk) + 1);
			ft_strcpy(temp, bk);
			free(w->line);
			w->line = (char *)malloc(sizeof(char *) * ft_strlen(temp) + ft_strlen(str) + 1);
			ft_strcpy(w->line, temp);
			ft_strcat(w->line, str);
			w->line[ft_strlen(w->line)] = '`';
			w = ft_bquote(env, w);
			return (w);
		}
		return (w);
	}
	w->line = bk;
	return (w);
}

void	ft_doublecoms(t_env *env, t_main *w, int test)
{
	char		**coms;
	int 		i;

	i = 0;
	coms = NULL;
	ft_selectinit(w);
	if (test == 1)
	{
		w->line = NULL;
		while (ft_select(w, &w->line))
			;
	}
	ft_selectend(w);
	w->line = ft_strtrim(w->line);
	w = ft_keep_main(*w, 0);
	if (ft_findstr("`", w->line) != 0)
		w = ft_bquote(env, w);
	if (ft_findstr("&&", w->line) != 0 && ft_findstr("||", w->line) != 0 && (i = 1))
		ft_if_else(env, w);
	else if (ft_strchr(w->line, '|') != 0 && ft_ifindstr(w->line, "||") == -1)
		com_pipes(w, env, coms);
	else if ((ft_strchr(w->line, '>') != 0 || ft_strchr(w->line, '<') != 0 ))
		ft_redirect(w, env);
	else if (ft_strchr(w->line, ';') == 0)
		ft_minishell(env, w);
	else if (ft_strchr(w->line, '|') == 0 && ft_strchr(w->line, ';') != 0)
		semicolon(w, env, coms);
	if (i == 0 && test == 1)
	{
		ft_putstr("calling myself");
		free(w->line);
		ft_doublecoms(env, w, 1);
	}
}
