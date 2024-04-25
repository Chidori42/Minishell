/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/25 03:07:24 by bramzil          ###   ########.fr       */
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
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
// # define malloc(void) NULL
//******************************* command node *******************************//

typedef struct   s_cmd
{
	int				in;
	int				out;
	char			**data;
	char			**redir;
	struct s_cmd	*next;
}					t_cmd;

//**************************** minishell struture ****************************//

typedef struct  s_pars
{
	int			ext_st;
	char		*def_path;
	char		*input;
	char		**tab;
	char		**envp;
	t_cmd		*lst;
}				t_pars;

//*********************** minishell function prototypes: *********************//

int		ft_get_redir(char ***redir, char **tab, int i);
int		ft_get_cmd(char ***data, char **tab, int i);
int		ft_set_last_arg(t_pars *args, char **tab);
int		ft_create_list(t_pars *args, char **tab);
int		ft_split_input(char ***tab, char *input);
int		ft_scape_quotes(char *input, int i);
int		ft_heredoc(t_pars *ags, char **lim);
int		ft_check_redir(char *s, int *i);
int 	ft_resplit_input(char ***tab);
void	ft_remove_quotes(t_cmd *lst);
int		ft_count_words(char *input);
int		ft_is_there_quotes(char *s);
int		ft_is_builtin(char **tab);
void	ft_free_list(t_cmd *lst);
int		ft_free_2_dm(char **arr);
char	*ft_remove_qts(char *s);
void	ft_heredoc_signals();
void	ft_parent_signals();
int		ft_is_redir(char *s);
int		ft_check_quotes(char *s);
void	ft_parse_error(char *str);
int		ft_dup_fd(int new, int old);
int		ft_execute_lst(t_pars *args);
char	*ft_inject_space(char *input);
int		ft_strcmp(char *s_1, char *s_2);
char	*ft_strs_join(char *s1, char *s2);
char 	*ft_getenv(char **envp, char *name);
int		ft_expander(t_pars *args, char **tab);
int		ft_find_second(char *s, char qt, int i);
int		ft_check_parse(t_pars *args, char **tab);
int		ft_execute_cmd(t_pars *args, t_cmd *node);
int		ft_redirection(t_pars *args, t_cmd *node);

//****************************************************************************//
int		ft_var_len(char *arg);
int		ft_check_arg(char *arg);
int		ft_check_var(char *arg);
void	ft_display_env(t_pars *data);
int		ft_unset(t_pars *arg, char **p);
char	**ft_dup_env(char **envp, char *var);
int		ft_export(t_pars *data, char **args);
void	ft_set_env(t_pars *data, char **env);
int		ft_builtins(t_cmd *cmd, t_pars *arg, int i);
char	**ft_check_set(char **envp, char *v_name, char *str);

#endif

//****************************************************************************//