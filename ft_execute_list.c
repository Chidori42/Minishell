/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:46:25 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 20:25:21 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_initiate_fds(t_pars *args, int i, int b)
{
	if (b)
	{
		args->p_1[0] = 0;
		args->p_1[1] = 1;
		args->p_2[0] = 0;
		args->p_2[1] = 1;
	}
	else
	{
		if ((i % 2) != 0)
			args->p_2[1] = 1;
		else if ((i % 2) == 0)
			args->p_1[1] = 1;
	}
}

static int	ft_close_fd(t_pars *args, t_cmd *node, int i)
{
	if (i % 2 == 0)
	{
		if (args->p_1[0] != 0 && (args->p_1[0] != 0) && \
			(close(args->p_1[0]) < 0))
			return (ft_putendl_fd(strerror(errno), 2), -1);
		if (!node->next && (*node->out != 1 ) && \
			(close(*node->out) < 0))
			return (ft_putendl_fd(strerror(errno), 2), -1);
		args->p_1[0] = 0;
	} 
	else if ((i % 2 != 0))
	{
		if (args->p_2[0] != 0 && (args->p_2[0] != 0) && \
			(close(args->p_2[0]) < 0))
			return (ft_putendl_fd(strerror(errno), 2), -1);
		if (!node->next && (*node->out != 1 ) && \
			(close(*node->out) < 0))
			return (ft_putendl_fd(strerror(errno), 2), -1);
		args->p_2[0] = 0;
	}
	return (0);
}

static int	ft_pipe(t_pars *args, t_cmd *node, int i)
{
	if ((i == 1) && node->next && (pipe(args->p_1) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	else if (1 < i)
	{
		if (!node->next)
		{
			if ((i % 2 == 0) && ((close(args->p_1[1]) < 0)))
				return (ft_putendl_fd(strerror(errno), 2), -1);
			else if (i % 2 != 0 && ((close(args->p_2[1]) < 0)))
				return (ft_putendl_fd(strerror(errno), 2), -1);
		}
		else if ((i % 2 == 0) && \
			((close(args->p_1[1]) < 0) || (pipe(args->p_2) < 0)))
			return (ft_putendl_fd(strerror(errno), 2), -1);
		else if ((i % 2 != 0) && \
			((close(args->p_2[1]) < 0) || (pipe(args->p_1) < 0)))
			return (ft_putendl_fd(strerror(errno), 2), -1);
	}
	return (0); 
}

static int	ft_child(t_pars *args, t_cmd *node, int i)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd(strerror(errno), 2), 1);
	else if (pid == 0)
		ft_execute_cmd(args, node, i);
	ft_close_fd(args, node, i);
	return (0);
}

int	ft_execute_lst(t_pars *args)
{
	int			i;
	t_cmd		*lst;

	i = 0;
	lst = args->lst;
	ft_initiate_fds(args, 0, 1);
	while (lst && ++i)
	{
		if ((ft_pipe(args, lst, i) < 0) || \
			(ft_redirection(args, lst) < 0))
			return (1);
		ft_initiate_fds(args, i, 0);
		if (ft_is_builtin(lst->data) == 2)
			args->ext_st = ft_builtins(lst, args, i);
		else
			ft_child(args, lst, i);
		lst = lst->next;
	}
	while (0 < wait(&args->ext_st))
		;
	return (WEXITSTATUS(args->ext_st));
}

// bash-3.2$ sleep 100
// ^C
// bash-3.2$ echo $?
// 130
// bash-3.2$ sleep 100
// ^\Quit: 3
// bash-3.2$ echo $?
// 131
// bash-3.2$ 
// executable file must be handled (./minishell | ok, minishell | no)