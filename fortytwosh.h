/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twentyonesh.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcowle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 15:59:48 by kcowle            #+#    #+#             */
/*   Updated: 2016/09/09 14:52:50 by smahomed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTYTWOSH_H
# define FORTYTWOSH_H
# define STDIN	0
# define STDOUT	1
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include "libft/libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <termcap.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct		s_bquote
{
	int		i;
	int		j;
	int		length;
	int		x;
	int		save;
	int		num;
	char	*com;
	char	*bk;
	char	*line;
	int		fd[2];
	char	*str;
	char	*buf;
	char	*temp;
	char	*promt;
	char	**coms;
}					t_bquote;

typedef struct		s_execve
{
	int			*fd;
	int			x;
	int			u;
	int			y;
	int			n;
	int			k;
	int			i;
	int			length;
}					t_execve;

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
	char			**vars;
	int				fail;
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

typedef struct		s_tablst
{
	char			*name;
	struct s_tablst	*next;
}					t_tablst;

typedef struct		s_tab
{
	t_tablst		*lst;
	t_tablst		*pos;
	char			*dir;
	char			*tdir;
	char			*criteria;
	int				fh;
	int				fw;
	int				lh;
	int				cc;
	int				pb;
	t_tablst		*tmplst;
	int				rc;
	int				w;
	int				h;
	char			*sd;
	char			lb;
	int				v[1];
	char			ctrl_v;
	char			tb;
}					t_tab;

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
	t_tab			t;
	char			*pro;
	char			ret;
}					t_main;

typedef struct		s_keyhook
{
	char			*line;
	int				buffsize;
	int				cursor;
	int				buff;
	int				x;
	int				start;
	int				end;
	char			*pro;
	char			*clip;
	char			ctrl_v;
	int				lineprom;
	char			ret;
}					t_keyhook;

typedef struct		s_history
{
	int i;
	int start;
	int pos;
	int yes;
}					t_history;

int					is_tab_auto_fill0(t_main *e);
int					is_tab_auto_complete0(t_main *e);
void				reg_bquote(t_env *env, t_main *w, t_bquote bquote);
t_keyhook			*key_hook_init(t_keyhook *env);
t_keyhook			*key_hook_init(t_keyhook *env);
t_bquote			ft_bquote_init(t_bquote bquote, t_main *w);
t_bquote			ft_bquote1(t_env *env, char **line, t_bquote bquote);
t_main				*ft_bquote(t_env *env, t_main *w);
t_main				*ft_keep_main();
t_env				*set_env(char **line2, t_env *env);
t_env				*export_var(t_env *env, char **line);
t_env				*unset_var(t_env *env, char *line);
t_env				*ft_unsetenv(t_env *env, char *line);
t_env				get_dir(t_env *env, char **line);
t_env				ft_excecute(char **line2, int comcount, t_env *env);
t_env				*ft_keep_struct();
t_env				*ft_vars(t_env *env, t_main *w);
t_env				*change_var(t_env *env, char *line);
t_env				ft_slash(t_env *env, char **line2);
t_env				*ft_vars_insert(t_env *env, char **temp, int x, int i);
void				ft_and_or(t_main *w, t_env *env);
void				ft_or_and(t_main *w, t_env *env);
void				semicolon(t_main *w, t_env *env, char **coms);
void				ft_aa(t_env *env, t_main *w);
void				ft_pp(t_env *env, t_main *w);
void				ft_history(t_main *w);
void				exclamation_history(t_env *env, t_main *w);
void				remove_char(t_keyhook *env);
void				remove_last_char(t_keyhook *env);
void				ft_freet_main(t_main *w);
void				ft_free(t_env *env);
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
void				ft_doublecoms(t_env *env, t_main *w, int test);
void				ft_echo(t_env *env, char *line);
void				ft_exit(t_env *env, t_main *w);
void				ft_links(char *line);
void				ft_minishell2(t_env *env, t_main m);
void				ft_excve(t_env *env, char **com, int i, t_main *w);
void				redirection_lt(t_main *w, t_env *env);
void				redirection_gt(t_main *w, t_env *env, int append);
void				ft_redirect(t_main *w, t_env *env);
void				ft_history(t_main *w);
void				exclamation_history(t_env *env, t_main *w);
void				ft_if_else(t_env *env, t_main *w);
void				ft_pp(t_env *env, t_main *w);
void				ft_aa(t_env *env, t_main *w);
void				select_c(char c);
void				remove_last_char(t_keyhook *env);
void				remove_char(t_keyhook *env);
void				insert_char(t_keyhook *env, char c);
void				malloc_buff(t_keyhook *env);
void				printline(t_keyhook *env);
void				cut(t_keyhook *env);
void				paste(t_keyhook *env);
void				copy(t_keyhook *env);
void				main_init(t_main *main);
void				struct_init(t_env *env, int i);
int					ft_cleartablines(t_main *e);
int					ft_tabprint1(t_main *e);
int					ft_selectlinedel(void);
int					ft_tabprintpossibilities(t_main *e);
int					is_tab_auto_fill2(t_main *e, struct dirent *dp,
		int x, int t);
int					tab_getdir1(t_main *e, int ib, int z, char t[2][1024]);
int					is_tab_auto_fill1(t_main *e);
int					ft_tabprint(t_main *e);
int					ft_tabassign(t_main *e, char *s);
int					tab_skip(t_main *e);
int					tab_getdir(t_main *e);
int					is_tab_printed(t_main *e);
int					is_tab_auto_fill(t_main *e);
int					ft_tab(t_main *e);
int					ft_selectremalloc(t_main *e);
int					ft_select2(t_main *e, char b[4]);
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
int					ft_ctrlup(int cursor, int x);
int					ft_ctrldown(int cursor, int x);
int					ft_isbuiltin(t_env *env, t_main *w);
int					ft_tilde_cd(int change, char **tmp, char **home);
int					ft_cd_error(char *tmp, int change, char *home, t_env *env);
int					ft_builtin3(t_env *env, t_main *w);
int					ft_builtin2(t_env *env, t_main *w);
int					ctrl_v(t_keyhook *env, char buff[4]);
char				*get_path(t_env *env);
char				*is_history(char *str, t_21line_l *history);
char				*ft_getvar(t_env *env, char *text);
char				*get_str(char *promt, char ret);
char				*ft_getenv(t_env *env, char *text);
char				**ft_insert(t_env *env, char *com);
char				*variable_check(char *line);
char				**temp_return(t_env *env, int *i);
char				*is_var(char *line, t_env *env);
#endif
