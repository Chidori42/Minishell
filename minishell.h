/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/06 19:52:13 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//**************************** included header files *************************//

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
// # define malloc(void) NULL
int			G_sig;
# define RL_SIG rl_catch_signals

//******************************* command node *******************************//

typedef struct s_cmd
{
	int				in;
	int				out;
	char			**data;
	char			**redir;
	struct s_cmd	*next;
}					t_cmd;

//**************************** minishell struture ****************************//

typedef struct s_pars
{
	t_cmd		*lst;
	char		**tab;
	int			ext_st;
	char		**envp;
	char		*input;
	char		*cwd;
	char		*path;
}				t_pars;

//*********************** minishell function prototypes: *********************//

int		last_arg(t_pars *args, t_cmd *node, char **tab, int f);
int		ft_get_redir(char ***redir, char **tab, int i);
int		ft_redir_expand(t_pars *args, char ***redir);
int		ft_get_cmd(char ***data, char **tab, int i);
int		ft_create_list(t_pars *args, char **tab);
int		ft_split_input(char ***tab, char *input);
int		ft_scape_quotes(char *input, int i);
int		ft_heredoc(t_pars *ags, char **lim);
int		ft_check_redir(char *s, int *i);
int		ft_resplit_input(char ***tab);
int		ft_strstr(char *ref, char *s);
void	ft_remove_quotes(t_cmd *lst);
int		ft_count_words(char *input);
int		ft_is_there_quotes(char *s);
int		ft_is_onlyspace(char *str);
int		ft_is_builtin(char **tab);
void	ft_free_list(t_cmd *lst);
int		ft_free_2_dm(char **arr);
char	*ft_remove_qts(char *s);
int		ft_close(t_pars *args);
void	ft_signals(int sig);
int		ft_is_redir(char *s);
int		ft_check_quotes(char *s);
void	ft_child_handler(int sig);
void	ft_parse_error(char *str);
int		ft_execute_lst(t_pars *args);
char	*ft_inject_space(char *input);
int		ft_strcmp(char *s_1, char *s_2);
char	**ft_split_fr(char *str, char c);
char	*ft_strs_join(char *s1, char *s2);
int		ft_parse(t_pars *args, char **tab);
char	*ft_getenv(char **envp, char *name);
int		ft_redirection(t_cmd *node, int *st);
int		ft_dup_fd(int new, int old, int *st);
int		ft_expander(t_pars *args, char **tab);
int		ft_find_second(char *s, char qt, int i);
int		ft_execute_cmd(t_pars *args, t_cmd *node);
int		ft_get_status(pid_t new_pid, int *cont, int vl, int lvl);

//****************************************************************************//
void	ft_cd_error(void);
int		ft_exit(t_cmd *node);
int		ft_var_len(char *arg);
char	*ft_getcwd(t_pars *args);
char	*ft_get_operator(char *arg);
int		ft_unset(t_pars *arg, char **p);
int		ft_cd(t_pars *args, t_cmd *node);
int		ft_check_arg(char *arg, int *st);
int		ft_check_var(char *arg, int *st);
char	**ft_split_fre(char *str, char c);
char	*ft_new_var(char *var, char *old_vl);
void	ft_set_env(t_pars *data, char **env);
int		ft_builtins(t_pars *arg, t_cmd *node);
void	ft_display_env(t_pars *data, t_cmd *node);
int		ft_dup_env(char **envp, char ***new, char *var);
void	ft_builts_error(char *name, char *str, char *des);
int		ft_export(t_pars *args, t_cmd *node, char **pars);
int		ft_update_env(char **envp, char *arg, int *b, int i);
#endif

//****************************************************************************//