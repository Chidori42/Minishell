/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:15 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/23 20:23:07 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **p)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (p && p[++j])
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

	if (p && p[1])
		return (ft_putendl_fd("Invalid arg's number", 2), 1);
	else if (p && p[0])
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
	if (arg && str && str[1])
		return (ft_putendl_fd("Invalid arg's number", 2), 1);
	else if (arg)
	{
		while (arg->envp && arg->envp[++i])
		{
			if (ft_strchr(arg->envp[i], '='))
				printf("%s\n", arg->envp[i]);
		}
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
	if (p && p[1])
	{
		if (ft_strlen(p[1]) > 255)
			return (ft_putendl_fd("file name to long!", 2), -1);
		else if (chdir(p[1]) != 0)
			return (ft_putendl_fd(strerror(errno), 2), -1);
	}
	else if (data && data->envp)
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

int	ft_builtins(t_cmd *cmd, t_pars *arg, int i)
{
	printf("########## from builtins ###############\n");
	if (cmd && !cmd->next && (i == 1) && cmd->data && arg)
	{
		if (!ft_strcmp(cmd->data[0], "export"))
			return (ft_export(arg, cmd->data));
		else if (!ft_strcmp(cmd->data[0], "cd"))
			return (ft_cd(arg, cmd->data));
		else if (!ft_strcmp(cmd->data[0], "pwd"))
			return (ft_pwd(cmd->data));
		else if (!ft_strcmp(cmd->data[0], "env"))
			return (ft_env(arg, cmd->data));
		else if (!ft_strcmp(cmd->data[0], "echo"))
			return (ft_echo(cmd->data));
		else if (!ft_strcmp(cmd->data[0], "unset"))
			return (ft_unset(arg, cmd->data));
		else if (!ft_strcmp(cmd->data[0], "exit"))
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
	}
	return (10);
}
