/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/29 10:48:20 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_cmd
{
	int				in;
	int				out;
	char			**data;
	char			*redir;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_pars
{
	int			p_1[2];
	int			p_2[2];
	int			pid;
	char		*input;
	char		**tab;
	char		**envp;
	t_cmd		*lst;
}		t_pars;

int		ft_free(char **str);
int		if_change(char *str);
char	*ft_is_complet(void);
int		ft_check_parse(char *s);
void	ft_free_list(t_cmd *lst);
int		ft_free_2_dm(char **arr);
int		ft_check_quotes(char *s);
void	ft_parse_error(char *str);
int		isvalid_var_name(char *str);
int		ft_redirection(t_cmd *node);
t_cmd	*ft_create_list(char **tab);
int		ft_execute_lst(t_pars *args);
void	ft_remove_quotes(char **tab);
char	**ft_split_input(char *input);
int		ft_check_parenthesis(char *s);
char	*ft_inject_space(char *input);
int		ft_unset(t_pars *arg, char **p);
int		ft_check_redir(char *s, int *i);
char	**ft_get_cmd(char **tab, int i);
int		ft_check_flu_ct(char *s, int i);
int		ft_strcmp(char *s_1, char *s_2);
int		ft_export(t_pars *arg, char **p);
char	*ft_get_redir(char **tab, int i);
char	*ft_strs_join(char *s1, char *s2);
int		ft_scape_quotes(char *input, int i);
int		append_value(t_pars *arg, char *str);
int		ft_scape_parenth(char *input, int i);
char	**set_new_env(t_pars *arg, char *str);
void	ft_builthing(t_cmd *cmd, t_pars *arg);
int		ft_find_second(char *s, char qt, int i);
int		check_repeat_var(t_pars *arg, char *str, char *tmp);

#endif