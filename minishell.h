/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeltif <abdeltif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:25:22 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/28 01:35:39 by abdeltif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 1486969768
# endif

# include <unistd.h>
# include <stdio.h>
# include <string.h>
#include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	**tab;
	char 	**envp;
	char 	**cmds;
	char 	**opers;
	int		sig;
	int		pid;
	char 	*str;
}       t_data;

int     ft_strlen(char *s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
char	*ft_itoa(int nbr);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlcpy(char *dst, char *src, int len);
void	ft_putchar_fd(char c, int fd);
void	ft_strcat(char *dest, const char *src);
int		isvalid_var_name(char *str);
int		ft_free(char **str);
void	ft_strcpy(char *dest, char *src);
char	*get_next_line(int fd);
void    set_parameter(t_data *arg);
char	**ft_split(char *s, char c);
char	*ft_substr(char *s, int start, int len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void    ft_builthing(t_data *arg);
int     ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *src);
void	parcing(t_data *arg);
int		ft_env(t_data *arg, char *str);
int		ft_echo(char *p);
char	*ft_help_exp(char *p);
int		ft_export(t_data *arg, char *p);
char	**set_new_env(t_data *arg, char *str);
int		ft_check_vars(char **str);
char	*get_var_name(char *str, char	*op);
char	*my_getenv(t_data *arg, char *name);
void	ft_expand(t_data *arg, char **str);
int		if_change(char *str);
int		append_value(t_data *arg, char *str);
int		check_repeat_var(t_data *arg, char *str, char *tmp);
int		ft_unset(t_data *arg, char *p);

#endif