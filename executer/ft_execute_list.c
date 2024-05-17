/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:46:25 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/14 20:34:20 by ael-fagr         ###   ########.fr       */
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

static int	ft_get_exit(t_pars *args, pid_t rt)
{
	int			b;
	int			st;
	pid_t		pid;

	b = 0;
	st = -1;
	while (true)
	{
		pid = wait(&st);
		if (0 < pid && (rt == pid) && ++b && WIFSIGNALED(st))
			ft_get_status(rt, NULL, (WTERMSIG(st) + 128), 3);
		else if (0 < pid && (rt == pid) && ++b)
			ft_get_status(rt, NULL, WEXITSTATUS(st), 3);
		if (g_sig == 3)
			tcsetattr(fileno(stdout), TCSANOW, &args->term_st);
		if (pid < 0)
			break ;
	}
	if (!b && !g_sig)
		ft_get_status(0, NULL, rt, 2);
	return (0);
}

static int	ft_pipe(t_cmd *node, int *st)
{
	int			p[2];

	if (node->next)
	{
		if (pipe(p) < 0)
		{
			ft_putendl_fd(strerror(errno), 2);
			return (((*st) = 1), -1);
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
			return (ft_putendl_fd(strerror(errno), 2), \
				kill(0, SIGINT), -1);
		else if (pid == 0)
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

int	ft_executer(t_pars *args)
{
	int			i;
	int			st;
	t_cmd		*lst;

	i = 0;
	st = 0;
	lst = args->lst;
	while (0 <= st && lst && ++i)
	{
		last_arg(args, lst, lst->data, i);
		if (!ft_pipe(lst, &st) && \
			!ft_redirection(args, lst, &st))
		{
			if ((i == 1) && !lst->next && \
				ft_is_builtin(lst->data))
				st = ft_builtins(args, lst);
			else if (lst->data)
				st = ft_child(args, lst);
		}
		ft_close_fd(lst);
		lst = lst->next;
	}
	return (ft_get_exit(args, st));
}
