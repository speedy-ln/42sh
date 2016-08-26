/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knage <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 07:30:39 by knage             #+#    #+#             */
/*   Updated: 2016/08/23 13:16:08 by kcowle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwosh.h"

void	print_env(t_env *env)
{
	int i;

	i = 0;
	while (env->enviro[i] != NULL)
	{
		ft_putstr(env->enviro[i]);
		ft_putchar('\n');
		i++;
	}
}

t_env	*set_env(char **line2, t_env *env)
{
	int		i;
	char	*temp;
	char	**envirok;

	i = 1;
	if (ft_strlen2D(line2) == 3)
	{
		while (line2[1] && env->enviro[i] != NULL)
		{
			if (ft_strncmp(line2[1], env->enviro[i], 4) == 0)
			{
				free(env->enviro[i]);
				temp = ft_strjoin(line2[1], "=");
				env->enviro[i] = ft_strjoin(temp, line2[2]);
				free(temp);
				return (env);
			}
			i++;
		}
		envirok = (char**)malloc(sizeof(char**) * i + 2);
		i = 0;
		while (line2[1] && env->enviro[i] != NULL)
		{
			envirok[i] = ft_strnew(ft_strlen(env->enviro[i]) + 1);
			ft_strcpy(envirok[i], env->enviro[i]);
			i++;
		}
		temp = ft_strjoin(line2[1], "=");
		envirok[i] = ft_strjoin(temp, line2[2]);
		free(temp);
		i++;
		envirok[i] = 0;
		ft_free2d(env->enviro);
		env->enviro = envirok;
	}
	return (env);
}

t_env	*ft_unsetenv(t_env *env, char *line)
{
	int 	i;
	int 	j;
	int		size;
	char	**temp;

	i = 0;
	j = 0;
	size = ft_strlen(line);
	if (size != 0)
	{
		while (env->enviro[i])
			i++;
		temp = (char**)malloc(sizeof(char**) * i + 1);
		i = 0;
		while (env->enviro[i] != NULL)
		{
			if (ft_strncmp(env->enviro[i], line, size) == 0)
				;
			else
			{
				temp[j] = ft_strdup(env->enviro[i]);
				j++;
			}
			i++;
		}
		ft_free2d(env->enviro);
		temp[j] = 0;
		env->enviro = temp;
	}
	return (env);
}

void	main_init(t_main *main)
{
	main->line = NULL;
	main->start = -2;
	main->clip = NULL;
	main->buffsize = 0;
	main->a = 0;
	main->y = -1;
	main->lineprom = 0;
	main->quote = 2;
	main->open = 0;
	ft_init(main);
}

int		main(void)
{
	t_env			*env;
	extern char		**environ;
	int				i;
	int				n;
	t_main			*w;

	n = 0;
	i = 0;
	w = ft_keep_main();
	env = ft_keep_struct();
	env->prev_pwd = NULL;
	env->cont = 0;
	env->father = 0;
	env->vars = 0;
	w->pro = (char *)malloc(sizeof(char *) * ft_strlen("<<^>>: "));
	ft_strcpy(w->pro, "<<^>>: ");
	w->ret = '\n';
	while (environ[i] != NULL)
		i++;
	env->enviro = (char **)malloc(sizeof(char **) * i + 1);
	env->envirobk = (char **)malloc(sizeof(char **) * i + 1);
	while (n < i)
	{
		env->enviro[n] = (char *)malloc(sizeof(char *) * ft_strlen(environ[n]));
		env->envirobk[n] = (char *)malloc(sizeof(char *) *\
				ft_strlen(environ[n]));
		ft_strcpy(env->enviro[n], environ[n]);
		ft_strcpy(env->envirobk[n], environ[n]);
		n++;
	}
	main_init(w);
	signal(SIGINT, sinno);
	ft_doublecoms(env, w, 1);
	return (0);
}
