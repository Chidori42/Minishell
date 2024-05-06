/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:46:25 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/05 23:55:58 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_close_fd(t_cmd *node)
{
	if ((2 < node->in) && (close(node->in) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	if ((2 < node->out) && (close(node->out) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (0);
}

static int ft_get_exit(pid_t pid_1)
{
	int 		i;
	int			st;
	pid_t		pid;
	
	i = 0;
	st = -1;
	if (200 < pid_1)
		pid_1 = 0;
	while (true)
	{
		pid = wait(&st);
		if (0 < pid)
		{
			if (WIFSIGNALED(st))
				ft_get_status(pid_1, 128 + st, 1);
			else if ((pid_1 == pid) && ++i)
				ft_get_status(pid_1, WEXITSTATUS(st), 1);
		}
		else
			break ;
	}
	if ((st == -1) && !i)
		ft_get_status(getpid(), pid_1, 1);
	return (0);
}

static int	ft_pipe(t_cmd *node)
{
	int			p[2];
	
	if (node->next)
	{
		if (pipe(p) < 0)
		{
			ft_get_status(getpid(), 1, 1);
			ft_putendl_fd(strerror(errno), 2);
			return (-1);
		}
		node->out = p[1];
		node->next->in = p[0];
	}
	return (0); 
}

static pid_t	ft_child(t_pars *args, t_cmd *node)
{
	int			st;
	pid_t		pid;

	if (node->data && node->data[0])
	{
		pid = fork();
		if (pid < 0)
			return (ft_putendl_fd(strerror(errno), 2), -1);
		if (pid == 0)
		{
			if (node->next && node->next->in && \
				(close(node->next->in) < 0))
				(ft_putendl_fd(strerror(errno), 2), exit(1));
			st = ft_execute_cmd(args, node);
			exit(st);
		}
		return (pid);
	}
	return (0);
}

int	ft_execute_lst(t_pars *args)
{
	int			i;
	int			st;
	t_cmd		*lst;

	i = 0;
	st = 0;
	lst = args->lst;
	while (lst && ++i)
	{
		last_arg(args, lst, lst->data, i);
		if (!ft_pipe(lst) && !ft_redirection(args, lst))
		{
			if ((i == 1) && !lst->next && \
				ft_is_builtin(lst->data))
				st = ft_builtins(args, lst);
			else
				st = ft_child(args, lst);
		}
		ft_close_fd(lst);
		lst = lst->next;
	}
	return (ft_get_exit(st));
}
