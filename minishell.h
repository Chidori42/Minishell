/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 03:22:32 by ael-fagr         ###   ########.fr       */
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
	int				*in;
	int				*out;
	char			**data;
	char			**redir;
	char 			**ref;
	struct s_cmd	*next;
}					t_cmd;

//**************************** minishell struture *****************************//

typedef struct  s_pars
{
	int			p_1[2];
	int			p_2[2];
	int			ext_st;
	char		*def_path;
	char		*input;
	char		**tab;
	char		**envp;
	t_cmd		*lst;
}				t_pars;

//*********************** minishell function prototypes: *********************//

char	**ft_get_cmd(t_pars *args, char **tab, int i);
t_cmd	*ft_create_list(t_pars *args, char **tab);
int		ft_check_parse(t_pars *args, char *s);
int		ft_scape_quotes(char *input, int i);
char	*ft_heredoc(t_pars *ags, char *lm);
int		ft_check_redir(char *s, int *i);
int		ft_check_flu_ct(char *s, int i);
char 	**ft_resplit_input(char **tab);
char	**ft_split_input(char *input);
void	ft_remove_quotes(t_cmd *lst);
int		ft_count_words(char *input);
int		ft_is_there_quotes(char *s);
int		ft_free_2_dm(char **arr);
void	ft_free_list(t_cmd *lst);
char	*ft_remove_qts(char *s);
void	ft_heredoc_signals();
void	ft_parent_signals();
int		ft_is_redir(char *s);
int		ft_check_quotes(char *s);
void	ft_parse_error(char *str);
int		ft_execution(t_pars *args);
int		ft_execute_lst(t_pars *args);
char	*ft_inject_space(char *input);
int		ft_strcmp(char *s_1, char *s_2);
char	*ft_strs_join(char *s1, char *s2);
char 	*ft_getenv(char **envp, char *name);
int		ft_expander(t_pars *args, char **tab);
int		ft_find_second(char *s, char qt, int i);
int		ft_redirection(t_pars *args, t_cmd *node);
char	**ft_get_redir(t_pars *args, char **tab, int i);
int		ft_execute_cmd(t_pars *args, t_cmd *node, int i);

/*********************************************************/
char	**ft_dup_env(char **envp, char *var);
int		ft_check_arg(char *arg);
int		ft_var_len(char *arg);
int		ft_check_var(char *arg);
int		ft_builthing(t_cmd *cmd, t_pars *arg);
int		ft_export(t_pars *data, char **args);
int		ft_unset(t_pars *arg, char **p);
char	**ft_check_set(char **envp, char *v_name, char *str);
void	ft_display_env(t_pars *data);
void	ft_set_env(t_pars *data, char **env);

#endif

//****************************************************************************//