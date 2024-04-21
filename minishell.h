/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 10:49:55 by ael-fagr         ###   ########.fr       */
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

typedef struct s_cmd
{
	int				*in;
	int				*out;
	char			**data;
	char			**redir;
	char			**ref;
	struct s_cmd	*next;
}					t_cmd;

//**************************** minishell struture **************************//

typedef struct s_pars
{
	int			p_1[2];
	int			p_2[2];
	int			ext_st;
	char		*input;
	char		**tab;
	char		**envp;
	t_cmd		*lst;
}				t_pars;

//*********************** minishell function prototypes: *********************//

int		ft_heredoc(t_pars *ags, char *lm, char *rf, int *fd);
t_cmd	*ft_create_list(t_pars *args, char **tab);
void	ft_expander(t_pars *args, char **tab);
int		ft_check_parse(t_pars *args, char *s);
int		ft_scape_quotes(char *input, int i);
char	**ft_get_redir(char **tab, int i);
char	**ft_get_cmd(char **tab, int i);
int		ft_check_redir(char *s, int *i);
char	**ft_split_input(char *input);
int		ft_is_there_quotes(char *s);
int		ft_free_2_dm(char **arr);
void	ft_free_list(t_cmd *lst);
void	ft_parent_signals(void);
void	ft_heredoc_signals(void);
int		ft_is_redir(char *s);
int		ft_check_quotes(char *s);
void	ft_parse_error(char *str);
int		ft_execution(t_pars *args);
void	ft_remove_quotes(t_cmd *lst);
int		ft_execute_lst(t_pars *args);
char	*ft_inject_space(char *input);
int		ft_check_flu_ct(char *s, int i);
int		ft_strcmp(char *s_1, char *s_2);
char	*ft_strs_join(char *s1, char *s2);
char	*ft_getenv(char **envp, char *name);
int		ft_find_second(char *s, char qt, int i);
int		ft_redirection(t_pars *args, t_cmd *node);
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

#endif