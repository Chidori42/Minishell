/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builthing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:15 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/29 13:43:36 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **p)
{
	int		j;
	int		i;

	j = 1;
	i = 0;
	while (p[j])
	{
		if (ft_strcmp(p[j], "-n") == 0)
			(i = 1, j++);
		printf("%s", p[j]);
		if (p[j + 1])
			printf(" ");
		j++;
	}
	if (i == 0)
		printf("\n");
	ft_free(p);
	return (0);
}

int	ft_pwd(char **p)
{
	char	tmp[256];

	if (p[1] && p[1][0] == '-')
		printf("%s: -%c: invalid option\n", p[0], p[1][1]);
	else
	{
		if (getcwd(tmp, sizeof(tmp)))
			printf("%s\n", tmp);
		else
			printf("Error\n");
	}
	ft_free(p);
	return (0);
}

int	ft_env(t_pars *arg, char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i != 1)
		printf("%s: %s: No such file or directory\n", str[0], str[1]);
	else
	{
		i = 0;
		while (arg->envp[i])
		{
			printf("%s\n", arg->envp[i]);
			i++;
		}
	}
	ft_free(str);
	return (0);
}

int	ft_cd(char **p)
{
	int		j;

	j = 0;
	while (p[j])
		j++;
	if (j > 1 && ft_strcmp("~", p[1]))
	{
		if (chdir(p[1]) != 0)
			printf("cd: %s : No such file or directory\n", p[1]);
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
			printf("Error\n");
	}
	ft_free(p);
	return (0);
}

void	ft_builthing(t_cmd *cmd, t_pars *arg)
{
	int	i;

	while (cmd)
	{
		i = 0;
		if (ft_strcmp(cmd->data[0], "echo") == 0)
			ft_echo(cmd->data);
		else if (ft_strcmp(cmd->data[0], "pwd") == 0)
			ft_pwd(cmd->data);
		else if (ft_strcmp(cmd->data[0], "env") == 0)
			ft_env(arg, cmd->data);
		else if (ft_strcmp(cmd->data[0], "cd") == 0)
			ft_cd(cmd->data);
		else if (ft_strcmp(cmd->data[0], "unset") == 0)
			ft_unset(arg, cmd->data);
		else if (ft_strcmp(cmd->data[0], "export") == 0)
			ft_export(arg, cmd->data);
		else if (ft_strcmp(cmd->data[0], "exit") == 0)
			exit(0);
		i++;
		cmd = cmd->next;
	}
}
