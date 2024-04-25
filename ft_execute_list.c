/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:46:25 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/25 03:36:06 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_close_fd(t_cmd *node)
{
	if ((node->in != 0) && (close(node->in) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	if ((node->out != 1) && (close(node->out) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (0);
}

static int	ft_pipe(t_cmd *node)
{
	int			p[2];
	
	if (node->next)
	{
		if (pipe(p) < 0)
			return (ft_putendl_fd(strerror(errno), 2), -1);
		node->out = p[1];
		node->next->in = p[0];
	}
	return (0); 
}

static int	ft_child(t_pars *args, t_cmd *node)
{
	int			st;
	pid_t		pid;

	st = 1;
	if (node->data && node->data[0])
	{
		pid = fork();
		if (pid < 0)
			ft_putendl_fd(strerror(errno), 2);
		else if (pid == 0)
		{
			if (node->next && (node->next->in != 0) && \
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
	t_cmd		*lst;

	lst = args->lst;
	while (lst)
	{
		ft_set_last_arg(args, lst->data);
		if ((ft_pipe(lst) < 0) || \
			(ft_redirection(args, lst) < 0))
			return (1);
		if (ft_is_builtin(lst->data) == 2)
			args->ext_st = ft_builtins(lst, args, 1);
		else
			args->ext_st = ft_child(args, lst);
		ft_close_fd(lst);
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