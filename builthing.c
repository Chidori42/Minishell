/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builthing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:15 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/15 19:19:20 by ael-fagr         ###   ########.fr       */
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
		printf("%s: -%c: invalid option\n", p[0], p[1][1]);
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
		printf("%s: %s: No such file or directory\n", str[0], str[1]);
	else
		while (arg->envp && arg->envp[++i])
			printf("%s\n", arg->envp[i]);
	return (0);
}

int	ft_cd(t_pars *data, char **p)
{
	int		j;
	char	*pwd;
	char	*cmd;

	j = 0;
	cmd = ft_strs_join(ft_strdup("export OLDPWD="),
		ft_strdup(getcwd(NULL, 0)));
	ft_export(data, data->envp, ft_split(cmd, ' '));
	while (p[j])
		j++;
	if (j > 1)
	{
		if (chdir(p[1]) != 0)
			printf("cd: %s : No such file or directory\n", p[1]);
		pwd = getcwd(NULL, 0);
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
			printf("Error\n");
		pwd = getenv("HOME");
	}
	cmd = ft_strs_join(ft_strdup("export PWD="), ft_strdup(pwd));
	ft_export(data, data->envp, ft_split(cmd, ' '));
	return (0);
}

void	ft_builthing(t_cmd *cmd, t_pars *arg)
{
	while (cmd)
	{
		if (!ft_strcmp(cmd->data[0], "export"))
			ft_export(arg, arg->envp, cmd->data);
		else if (!ft_strcmp(cmd->data[0], "cd"))
			ft_cd(arg, cmd->data);
		else if (!ft_strcmp(cmd->data[0], "pwd"))
			ft_pwd(cmd->data);
		else if (!ft_strcmp(cmd->data[0], "echo"))
			ft_echo(cmd->data);
		else if (!ft_strcmp(cmd->data[0], "unset"))
			ft_unset(arg, cmd->data);
		else if (!ft_strcmp(cmd->data[0], "exit"))
			exit(0);
		cmd = cmd->next;
	}
}
