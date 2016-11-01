/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/09/10 13:15:33 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

t_env		*ft_vars_support(t_env *env, t_main *w)
{
	int		x;
	int		i;
	char	**temp;

	i = 0;
	temp = (char **)malloc(sizeof(char **) * 2);
	temp[0] = NULL;
	if (env->vars != NULL)
		temp = temp_return(env, &i);
	ft_free2d(env->vars);
	w->line = ft_strtrim(w->line);
	temp[i] = (char *)malloc(sizeof(char *) * ft_strlen(w->line) + 1);
	temp[i + 1] = NULL;
	ft_strcpy(temp[i], w->line);
	x = ft_ifindstr(temp[i], "=") - 1;
	while (temp[i][x] != '\0' && ft_isalnum(temp[i][x]) && x >= 0)
		x--;
	if (++x == 0 && (x = ft_ifindstr(temp[i], "=") + 1))
		env = ft_vars_insert(env, temp, x, i);
	else
		ft_putstr("Only alpha numeric characters allowed for local variable\n");
	if (temp != NULL)
		ft_free2d(temp);
	return (env);
}

t_env		*ft_vars(t_env *env, t_main *w)
{
	char	*test;
	char	*tmp;
	char	*tmp2;
	int		test1;

	tmp = ft_strtrim(w->line);
	test = ft_strdup(w->line);
	test[ft_ifindstr(test, "=")] = '\0';
	tmp2 = ft_getvar(env, test);
	test1 = ft_strlen(tmp2);
	free(tmp);
	free(tmp2);
	tmp = NULL;
	if (test1 == 0)
		env = ft_vars_support(env, w);
	else
		env = change_var(env, w->line);
	env = ft_keep_struct(*env, 0);
	if (test != NULL)
		free(test);
	return (env);
}

void		ft_printvars(t_env *env)
{
	int i;

	i = 0;
	if (env->vars)
	{
		while (env->vars[i] != NULL)
		{
			ft_putstr(env->vars[i]);
			ft_putchar('\n');
			i++;
		}
	}
}

int			ft_builtin4(t_env *env, t_main *w, char **line2)
{
	int		i;
	char	*temp;

	if (((i = 0) || 1) && ft_strcmp(line2[0], "printvars") == 0 && ++i)
		ft_printvars(env);
	else if (ft_strchr(line2[0], '=') != 0 && (i = 1))
		env = ft_vars(env, w);
	else if (ft_strcmp(line2[0], "history") == 0 && (i = 1))
		ft_history(w);
	else if (ft_strncmp(line2[0], "export", 6) == 0 && (i = 1))
		env = export_var(env, line2);
	else if (ft_findstr("&&", w->line) == 1 && (i = 1))
		ft_aa(env, w);
	else if (ft_findstr("||", w->line) == 1 && (i = 1))
		ft_pp(env, w);
	else if (!ft_strcmp(line2[0], "echo") && ++i)
	{
		temp = ft_strfcut(w->line, 5);
		free(w->line);
		w->line = ft_strdup(temp);
		free(temp);
		ft_echo(env, w->line + 0 * ((temp = NULL) || 1));
	}
	return ((i == 0 && (i = ft_builtin2(env, w))) * 0 + i);
}

int			ft_isbuiltin(t_env *env, t_main *w)
{
	int		i;
	char	**line2;
	char	*temp;

	i = 0;
	line2 = ft_strsplit(w->line, ' ');
	temp = ft_strtrim(line2[0]);
	free(line2[0]);
	line2[0] = NULL;
	line2[0] = (char *)malloc(sizeof(char *) * ft_strlen(temp) + 1);
	ft_strcpy(line2[0], temp);
	free(temp);
	if (ft_strncmp(w->line, "cd", 2) == 0 && (i = 1))
		ft_cd(w->line, env);
	else if (ft_strcmp(w->line, "clear") == 0 && (i = 1))
		tputs(tgetstr("cl", NULL), 1, ft_ft_putchar);
	else if (ft_strncmp(w->line, "unsetenv", 7) == 0 && (i = 1))
		env = ft_unsetenv(env, line2[1]);
	else if (ft_strncmp(line2[0], "unset", 5) == 0 && (i = 1))
		env = unset_var(env, line2[1]);
	else if (i == 0)
		i = ft_builtin4(env, w, line2);
	if (line2 != NULL)
		ft_free2d(line2);
	return (i);
}
