/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builthing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:15 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/21 20:51:58 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *p)
{
	int		j;
	int		i;
	char	**str;

	j = 1;
	i = 0;
	str = ft_split(p, ' ');
	if (!str)
		return (ft_free(str), -1);
	// if (ft_strcmp(str[0], "echo") != 0)
	// 	return (printf("commond not found"), -1);
	while (str[j])
	{
		if (ft_strcmp(str[j], "-n") == 0)
			(i = 1, j++);
		printf("%s", str[j]);
		if (str[j + 1])
			printf(" ");
		j++;
	}
	if (i == 0)
		printf("\n");
	ft_free(str);
	return (0);
}

int	ft_pwd(char *p)
{
	char	**str;
	char	tmp[256];

	str = ft_split(p, ' ');
	if (!str)
		return (free(str), -1);
	// if (ft_strcmp(str[0], "pwd") != 0)
	// 	return (printf("commond not found"), -1);
	if (str[1] && str[1][0] == '-')
		printf("%s: invalid option", str[0]);
	else
	{
		if (getcwd(tmp, sizeof(tmp)))
		{
			ft_putstr_fd(tmp, 1);
			ft_putchar_fd('\n', 1);
		}
		else
			printf("Error\n");
	}
	ft_free(str);
	return (0);
}

int	ft_env(t_data *arg, char *str)
{
	int		i;
	char	**p;

	i = 0;
	(void)arg;
	p = ft_split(str, ' ');
	if (!p)
		return (ft_free(p), -1);
	// if (ft_strcmp(p[0], "env") != 0)
	// 	return (printf("commond not found"), -1);
	while (p[i])
		i++;
	if (i != 1)
		printf("%s: %s: No such file or directory\n", p[0], p[1]);
	else
	{
		i = 0;
		while (arg->envp[i])
		{
			printf("%s\n", arg->envp[i]);
			i++;
		}
	}
	ft_free(p);
	return (0);
}
 
int	ft_cd(char *p)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = ft_split(p, ' ');
	if (!tmp)
		return (ft_free(tmp), -1);
	// if (ft_strcmp(tmp[0], "cd") != 0)
	// 	return (printf("commond not found"), -1);
	while (tmp[j])
		j++;
	if (j > 1)
	{
		if (chdir(tmp[1]) != 0)
			printf("%s : Not a directory\n", tmp[1]);
	}
	else
	{
		if (chdir("~") != 0)
			perror("Error\n");
	}
	ft_free(tmp);
	return (0);
}

void ft_builthing(t_data *arg)
{
	int i;

	i = 0;
	while (arg->cmds[i])
	{
		if (ft_strncmp(arg->cmds[i], "echo", 4) == 0)
			ft_echo(arg->cmds[i]);
		else if (ft_strncmp(arg->cmds[i], "pwd", 3) == 0)
			ft_pwd(arg->cmds[i]);
		else if (ft_strncmp(arg->cmds[i], "env", 3) == 0)
			ft_env(arg, arg->cmds[i]);
		else if (ft_strncmp(arg->cmds[i], "cd", 2) == 0)
			ft_cd(arg->cmds[i]);
		else if (ft_strncmp(arg->cmds[i], "unset", 5) == 0)
			ft_unset(arg, arg->cmds[i]);
		else if (ft_strncmp(arg->cmds[i], "export", 6) == 0)
			ft_export(arg, arg->cmds[i]);
		else if (ft_strncmp(arg->cmds[i], "exit", 4) == 0)
			exit(0);
		i++;
	}
	ft_free(arg->cmds);
}
