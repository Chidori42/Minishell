/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:49:21 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/07 09:53:33 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_fd(t_pars *args, int i)
{
	if (((i % 2) != 0) && (args->p_1[0] != 0) && \
		(close(args->p_1[0]) < 0))
		ft_putendl_fd(strerror(errno), 2);
	else if (((i % 2) == 0) && (args->p_2[0] != 0) && \
		(close(args->p_2[0]) < 0))
		ft_putendl_fd(strerror(errno), 2);
}

static char	*ft_get_path(char *cmd)
{
	int			i;
	char		**paths;
	char		*cmd_path;

	i = -1;
	cmd_path = cmd;
	paths = ft_split(getenv("PATH"), ':');
	if (paths)
	{
		while (paths[++i])
		{
			paths[i] = ft_strs_join(paths[i], ft_strdup("/"));
			cmd_path = ft_strs_join(ft_strdup(paths[i]), \
				ft_strdup(cmd));
			if (0 <= access(cmd_path, 01111))
				return (ft_free_2_dm(paths), cmd_path);
			free (cmd_path);
			cmd_path = NULL;
		}
	}
	return (ft_free_2_dm(paths), cmd);
}

int	ft_execute_cmd(t_pars *args, t_cmd *node, int i)
{
	char		*cmd_path;
	char		*error_msg;

	ft_close_fd(args, i);
	cmd_path = ft_get_path(node->data[0]);
	if ((0 <= dup2(*node->in, 0)) && (0 <= dup2(*node->out, 1)))
	{
		if (execve(cmd_path, node->data, args->envp) < 0)
		{
			error_msg = ft_strjoin("Error: command not found: ", \
				node->data[0]);
			ft_putendl_fd(error_msg, 2);
			free (error_msg);
		}
	}
	else
		ft_putendl_fd(strerror(errno), 2);
	exit(1);
}
