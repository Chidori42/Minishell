/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:15 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/22 21:10:45 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **p)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (p[++j])
	{
		while (p[j] && !ft_strcmp(p[j], "-n") && ++i)
			j++;
		if (p[j])
		{
			printf("%s", p[j]);
			if (p[j + 1])
				printf(" ");
		}
	}
	if (i == 0)
		printf("\n");
	return (0);
}

int	ft_pwd(char **p)
{
	char	tmp[256];

	if (p[1])
		return (ft_putendl_fd("Invalid arg's number", 2), 1);
	else
	{
		if (getcwd(tmp, sizeof(tmp)))
			printf("%s\n", tmp);
		else
			return (ft_putendl_fd("getcwd failure", 2), 1);
	}
	return (0);
}

int	ft_env(t_pars *arg, char **str)
{
	int		i;

	i = -1;
	if (str[1])
		return (ft_putendl_fd("Invalid arg's number", 2), 1);
	else
		while (arg->envp && arg->envp[++i])
		{
			if (ft_strchr(arg->envp[i], '='))
				printf("%s\n", arg->envp[i]);
		}
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
			return (ft_putendl_fd("file name to long!", 2), -1);
		else if (chdir(p[1]) != 0)
			return (ft_putendl_fd(strerror(errno), 2), -1);
	}
	else
	{
		cmd = ft_getenv(data->envp, "HOME");
		if (chdir(cmd) != 0)
			return (free(cmd), ft_putendl_fd(strerror(errno), 2), -1);
		free(cmd);
	}
	cmd = ft_strs_join(ft_strdup("export PWD="), getcwd(NULL, 0));
	(tmp = ft_split(cmd, ' '), ft_export(data, tmp));
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
