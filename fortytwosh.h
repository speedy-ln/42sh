/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twentyonesh.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 15:59:48 by kcowle            #+#    #+#             */
/*   Updated: 2016/08/11 10:29:33 by knage            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTYONESH_H
# define TWENTYONESH_H
# define STDIN	0
# define STDOUT	1
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include "libft/libft.h"
# include <dirent.h>
# include <libc.h>
# include <stdlib.h>
# include <unistd.h>
# include <termcap.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct  s_execve
{
    int         *fd;
    int         x;
    int         u;
    int         y;
    int         n;
    int         k;
    int         i;
    int         length;
}               t_execve;

typedef struct		s_21line_l
{
	char			*line;
	int				buff;
	int				x;
}					t_21line_l;

typedef struct		s_env
{
	pid_t			father;
	char			*path;
	char			**cmd;
	char			**args;
	char			**env;
	char			**enviro;
	char			**envirobk;
	int				cont;
	int				i;
	char			**history;
	char			*prev_pwd;
}					t_env;

typedef struct		s_echo
{
	int				state;
	int				state2;
	int				newline;
	char			**line2;
	int				e;
	int				o;
	int				i;
}					t_echo;

typedef struct		s_main
{
	struct termios	term;
	char			*line;
	char			**line2;
	int				comcount;
	int				v[4];
	t_21line_l		*a;
	int				buffsize;
	int				cursor;
	int				y_cursor;
	int				y;
	int				start;
	int				end;
	char			*clip;
	int				lineprom;
	int				quote;
	int				open;
}					t_main;

typedef struct		s_excve
{
	int	x;
	int	u;
	int	y;
	int	n;
	int	k;
	int	length;
}					t_excve;

int					ft_selectremalloc(t_main *e);
int					ft_cursor(char c);
int					ft_selectdelete(t_main *e);
int					ft_selectinsert(t_main *e, char c);
int					ft_selectbackspace(t_main *e);
int					ft_printstring(t_main *e);
int					ft_select(t_main *e, char **line);
int					ft_init(t_main *e);
int					ft_ft_putchar(int c);
int					ft_selectinit(t_main *env);
int					ft_selectend(t_main *env);
int					oct_dec(int n);
int					ft_handle1(char *line, char **line2, int *e, int *o);
int					ft_pow(int i, int x);
int					ft_linextention(t_main *e);
int					ft_ctrlup(t_main *e);
int					ft_ctrldown(t_main *e);
int					ft_isbuiltin(t_env *env, char *line);
char				*get_path(t_env *env);
char				**ft_insert(t_env *env, char *com);
t_env				*set_env(char **line2, t_env *env);
t_env				*ft_unsetenv(t_env *env, char *line);
t_env				get_dir(t_env *env, char **line);
t_env				ft_excecute(char **line2, int comcount, t_env *env);
t_env				*ft_keep_struct(t_env env, int i);
t_main				*ft_keep_main(t_main w, int i);
void				ft_cd(char *line, t_env *env);
void				ft_printoct(char *line, int *i);
void				ft_handle2(char *line, t_echo *ec);
void				ft_minishell(t_env *env, t_main *m);
void				print_env(t_env *env);
void				ft_pipes(t_env *env, char **coms, int i, t_main *w);
void				ft_handle3(t_echo *ec, char *line);
void				init_echo(char *line, t_echo *ec);
void				ft_copy(t_main *env);
void				ft_paste(t_main *env);
void				ft_cut(t_main *env);
void				sinno(int signall);
void				ft_free2d(char **array);
void				is_quote(t_main *main, char *str);
void				ft_fdfuncs(char *line);
void				ft_doublecoms(t_env *env, t_main *w);
void				ft_echo(t_env *env, char *line);
void				ft_exit(t_env *env, t_main *w);
void				ft_links(char *line);
void				ft_minishell2(t_env *env, t_main m);
void				ft_excve(t_env *env, char **com, int i, t_main *w);
void				redirection_lt(t_main *w, t_env *env);
void				redirection_gt(t_main *w, t_env *env, int append);
void				ft_redirect(t_main *w, t_env *env);
#endif
