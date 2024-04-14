/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/14 17:35:56 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//**************************** included header files *************************//

# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

//******************************* command node *******************************//

typedef struct s_cmd
{
	int				*in;
	int				*out;
	char			**data;
	char			**redir;
	char			**hered;
	struct s_cmd	*next;
}					t_cmd;

//*************************** minishell struture **************************//

typedef struct s_pars
{
	int			p_1[2];
	int			p_2[2];
	int			pid;
	char		*input;
	char		**tab;
	char		**envp;
	t_cmd		*lst;
}				t_pars;

//*********************** minishell function prototypes: *********************//

t_cmd	*ft_create_list(t_pars *args, char **tab);
int		ft_scape_quotes(char *input, int i);
char	**ft_get_redir(char **tab, int i);
int		ft_check_redir(char *s, int *i);
char	**ft_get_cmd(char **tab, int i);
char	**ft_split_input(char *input);
int		ft_redirection(t_cmd *node);
int		ft_check_last(char *input);
int		ft_heredoc(char	*limiter);
int		ft_free_2_dm(char **arr);
void	ft_free_list(t_cmd *lst);
int		ft_check_parse(char *s);
void	ft_expander(char **tab);
int		ft_is_redir(char *s);
char	*ft_is_complet(void);
int		ft_check_quotes(char *s);
void	ft_parse_error(char *str);
void	ft_remove_quotes(t_cmd *lst);
int		ft_execute_lst(t_pars *args);
char	*ft_inject_space(char *input);
int		ft_check_flu_ct(char *s, int i);
int		ft_strcmp(char *s_1, char *s_2);
char	*ft_strs_join(char *s1, char *s2);
int		ft_find_second(char *s, char qt, int i);
int		ft_execute_cmd(t_pars *args, t_cmd *node, int i);

/**********************************My Update**********************************/

char	**ft_dup_env(char **envp, char *var);
int		ft_check_arg(char *arg);
int		ft_var_len(char *arg);
int		ft_check_var(char *arg);
void	ft_builthing(t_cmd *cmd, t_pars *arg);
char	**ft_export(t_pars *data, char **envp, char **args);
int		isvalid_var_name(char *str);
int		check_repeat_var(t_pars *arg, char *str, char *tmp);
int		ft_unset(t_pars *arg, char **p);
void	print_env(t_pars *arg);
int		append_value(t_pars *arg, char *str);
int		set_to_env(t_pars *arg, char *str, int i);
char	*get_value_name(char *str, char	*op);
int		if_change(char *str);
int		ft_free(char **str);

#endif