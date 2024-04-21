/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:15 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/21 09:58:44 by ael-fagr         ###   ########.fr       */
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
		while (!ft_strcmp(p[j], "-n"))
		{
			i = 1;
			j++;
		}
		printf("%s", p[j]);
		if (p[j + 1])
			printf(" ");
		j++;
	}
	if (i == 0)
		printf("\n");
	return (0);
}

int	ft_pwd(char **p)
{
	char	tmp[256];

	if (p[1] && p[1][0] == '-')
	{
		printf("%s: -%c: invalid option\n", p[0], p[1][1]);
		return (1);
	}
	else
	{
		if (getcwd(tmp, sizeof(tmp)))
			printf("%s\n", tmp);
		else
			printf("Error\n");
	}
	return (0);
}

int	ft_env(t_pars *arg, char **str)
{
	int		i;

	i = -1;
	if (str[1])
	{
		printf("%s: %s: No such file or directory\n", str[0], str[1]);
		return (1);
	}
	else
		while (arg->envp && arg->envp[++i])
			printf("%s\n", arg->envp[i]);
	return (0);
}

int	ft_cd(t_pars *data, char **p)
{
	char	*cmd;
	char	**tmp;

	cmd = ft_strs_join(ft_strdup("export OLDPWD="), getcwd(NULL, 0));
	tmp = ft_split(cmd, ' ');
	ft_export(data, tmp);
	(free(cmd), ft_free_2_dm(tmp));
	if (p[1])
	{
		if (ft_strlen(p[1]) > 255)
			return (printf("cd: %s: File name too long", p[1]), -1);
		else if (chdir(p[1]) != 0)
			return (printf("cd: %s : No such file or directory\n", p[1]), -1);
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
			printf("Error\n");
	}
	cmd = ft_strs_join(ft_strdup("export PWD="), getcwd(NULL, 0));
	tmp = ft_split(cmd, ' ');
	ft_export(data, tmp);
	(free(cmd), ft_free_2_dm(tmp));
	return (0);
}

int	ft_builthing(t_cmd *cmd, t_pars *arg)
{
	while (cmd)
	{
		if (!ft_strcmp(cmd->data[0], "export"))
			arg->ext_st = ft_export(arg, cmd->data);
		else if (!ft_strcmp(cmd->data[0], "cd"))
			arg->ext_st = ft_cd(arg, cmd->data);
		else if (!ft_strcmp(cmd->data[0], "pwd"))
			arg->ext_st = ft_pwd(cmd->data);
		else if (!ft_strcmp(cmd->data[0], "env"))
			arg->ext_st = ft_env(arg, cmd->data);
		else if (!ft_strcmp(cmd->data[0], "echo"))
			arg->ext_st = ft_echo(cmd->data);
		else if (!ft_strcmp(cmd->data[0], "unset"))
			arg->ext_st = ft_unset(arg, cmd->data);
		else if (!ft_strcmp(cmd->data[0], "exit"))
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		cmd = cmd->next;
	}
	return (arg->ext_st);
}
