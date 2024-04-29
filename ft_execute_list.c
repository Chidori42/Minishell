/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:46:25 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/28 01:37:02 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_close_fd(t_cmd *node)
{
	if ((2 < node->in) && (close(node->in) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	if ((2 < node->out) && (close(node->out) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (0);
}

static int ft_get_exit(int ext_st)
{
	int 		i;
	int			st;
	
	i = 0;
	st = 0;
	while (true)
	{
		if (wait(&st) != -1 && ++i)
			ft_get_exit_status(WEXITSTATUS(st), 1);
		else
			break ;
	}
	if (!i)
		ft_get_exit_status(ext_st, 1);
	return (0);
}

static int	ft_pipe(t_cmd *node)
{
	int			p[2];
	
	if (node->next)
	{
		if (pipe(p) < 0)
		{
			ft_get_exit_status(1, 1);
			ft_putendl_fd(strerror(errno), 2);
			return (-1);
		}
		node->out = p[1];
		node->next->in = p[0];
	}
	return (0); 
}

static int	ft_child(t_pars *args, t_cmd *node)
{
	int			st;
	pid_t		pid;

	st = 0;
	if (node->data && node->data[0])
	{
		pid = fork();
		if (pid < 0)
			ft_putendl_fd(strerror(errno), 1);
		else if (pid == 0)
		{
			if (node->next && node->next->in && \
				(close(node->next->in) < 0))
				return (ft_putendl_fd(strerror(errno), 2), \
					exit(1), 1);
			st = ft_execute_cmd(args, node);
			exit(st);
		}
	}
	return (st);
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
		ft_set_last_arg(args, lst->data);
		if (ft_pipe(lst))
			return (-1);
		if ((i == 1) && !lst->next && \
			(ft_is_builtin(lst->data) == 2))
			st = ft_builtins(args, lst);
		else
			st = ft_child(args, lst);
		ft_close_fd(lst);
		lst = lst->next;
	}
	ft_get_exit(st);
	return (st);
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