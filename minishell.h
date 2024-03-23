/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:25:22 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/23 08:48:16 by ael-fagr         ###   ########.fr       */
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
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putchar_fd(char c, int fd);
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
char	**set_new_env(t_data *arg, char *p);
int		ft_unset(t_data *arg, char *p);

#endif