/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:14:00 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/12 02:15:26 by ael-fagr         ###   ########.fr       */
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
# include <termios.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
// # define malloc(void) NULL

//tests
/*
"echo $"  shouldn't expand
"unset PATH" no command should execute
exit state of ctr-c int prompt should be 1
*/

int		g_sig;
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
	t_cmd			*lst;
	char			**tab;
	int				ext_st;
	char			**envp;
	char			*input;
	char			*cwd;
	struct termios	term_st;
}				t_pars;

//*********************** minishell function prototypes: *********************//

//************************* parser function prototypes ***********************//

int		ft_check_quotes(char *s);
void	ft_parse_error(char *str);
int		ft_count_words(char *input);
char	*ft_inject_space(char *input);
int		ft_check_redir(char *s, int *i);
char	*ft_strs_join(char *s1, char *s2);
int		ft_parse(t_pars *args, char **tab);
int		ft_heredoc(t_pars *ags, char **lim);
int		ft_scape_quotes(char *input, int i);
int		ft_find_second(char *s, char qt, int i);
int		ft_split_input(char ***tab, char *input);

//************************ expander function prototypes **********************//

char	*ft_expand(t_pars *args, char *tp, char *rf, int en);
int		ft_expand_cmd(t_pars *args, char ***tab, int fl);
int		ft_encapsule_or(char *cmd, char *str, char *ref);
int		ft_get_redir(char ***redir, char **tab, int i);
int		ft_get_cmd(char ***data, char **tab, int i);
int		ft_create_list(t_pars *args, char **tab);
int		ft_expander(t_pars *args, t_cmd *lst);
char	*ft_expand_it(char *s, int fl);
int		ft_remove_scaper(char ***tab);
int		ft_remove_quotes(t_cmd *lst);
int		ft_resplit_tok(char ***tab);
int		ft_is_there_quotes(char *s);
char	*ft_add_scaper(char *str);
char	*ft_encapsule(char *str);
char	*ft_remove_qts(char *s);
int		ft_is_redir(char *s);

//************************* executer function prototypes ********************//

int		ft_get_status(pid_t new_pid, int *cont, int vl, int lvl);
int		last_arg(t_pars *args, t_cmd *node, char **tab, int f);
int		ft_execute_cmd(t_pars *args, t_cmd *node);
int		ft_redirection(t_cmd *node, int *st);
int		ft_dup_fd(int new, int old, int *st);
int		ft_strstr(char *ref, char *s);
int		ft_executer(t_pars *args);
int		ft_is_builtin(char **tab);
int		ft_redir_error(char *s);
int		ft_close(t_pars *args);

//**************************** utils function prototypes *********************//

void	ft_signals(int sig);
void	ft_free_list(t_cmd *lst);
int		ft_free_2_dm(char **arr);
int		ft_strcmp(char *s_1, char *s_2);
char	**ft_split_fr(char *str, char c);
char	*ft_getenv(char **envp, char *name);

//************************* builtins function prototypes *********************//

void	ft_cd_error(void);
int		ft_exit(t_cmd *node);
int		ft_var_len(char *arg);
char	*ft_getcwd(t_pars *args);
char	*ft_get_operator(char *arg);
int		ft_unset(t_pars *arg, char **p);
int		ft_cd(t_pars *args, t_cmd *node);
int		ft_check_arg(char *arg, int *st);
int		ft_check_var(char *arg, int *st);
void	ft_set_env(t_pars *data, char **env);
char	*ft_new_var(char *var, char *old_vl);
int		ft_builtins(t_pars *arg, t_cmd *node);
void	ft_print_value(t_cmd *node, char *str);
void	ft_display_env(t_pars *data, t_cmd *node);
int		ft_dup_env(char **envp, char ***new, char *var);
void	ft_builts_error(char *name, char *str, char *des);
int		ft_export(t_pars *args, t_cmd *node, char **pars);
int		ft_update_env(t_pars *args, char *par, int *b, int i);
#endif

//****************************************************************************//