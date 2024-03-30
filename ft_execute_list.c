/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:46:25 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/30 11:33:53 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_initiate_fds(t_pars *args)
{
	args->p_1[0] = 0;
	args->p_1[1] = 1;
	args->p_2[0] = 0;
	args->p_2[1] = 1;
}

static int	ft_close_fd(t_pars *args, int i)
{
	if (i % 2 == 0)
	{
		if (close(args->p_1[0]) < 0)
			return (perror("Error"), -1);
	} 
	else if ((1 < i) && (i % 2 != 0))
	{
		if (close(args->p_2[0]) < 0)
			return (perror("Error"), -1);
	} 
	return (0);
}

static int	ft_pipe(t_pars *args, t_cmd *node, int i)
{
	if ((i == 1) && node->next && (pipe(args->p_1) < 0))
		return (perror("Error"), -1);
	else if (1 < i)
	{
		if (!node->next)
		{
			if ((i % 2 == 0) && ((close(args->p_1[1]) < 0)))
				return (perror("Error"), -1);
			else if (i % 2 != 0 && ((close(args->p_2[1]) < 0)))
				return (perror("Error"), -1);
		}
		else if ((i % 2 == 0) && \
			((close(args->p_1[1]) < 0) || (pipe(args->p_2) < 0)))
			return (perror("Error"), -1);
		else if ((i % 2 != 0) && \
			((close(args->p_2[1]) < 0) || (pipe(args->p_1) < 0)))
			return (perror("Error"), -1);
	}
	return (0); 
}

static int	ft_dup(t_cmd *node, int i)
{
	if ((i == 1) && ((dup2(*node->out, 1) < 0) || \
		(dup2(*node->in, 0) < 0)))
		return (perror("Error"), -1);
	else if (1 < i)
	{
		if (!node->next)
		{
			if (((i % 2) == 0) && ((dup2(*node->in, 0) < 0) || \
				(dup2(*node->out, 1) < 0)))
				return (perror("Error"), -1);
			if (((i % 2) != 0) && ((dup2(*node->in, 0) < 0) || \
				(dup2(*node->out, 1) < 0)))
				return (perror("Error"), -1);
		}
		else if ((i % 2 == 0) && ((dup2(*node->in, 0) < 0) || \
			(dup2(*node->out, 1) < 0)))
			return (perror("Error"), -1);
		else if ((i % 2 != 0) && ((dup2(*node->in, 0) < 0) || \
			(dup2(*node->out, 1) < 0)))
			return (perror("Error"), -1);
	}
	return (0); 
}

int	ft_execute_lst(t_pars *args)
{
	int			i;
	int			pid;
	t_cmd		*lst;

	i = 1;
	lst = args->lst;
	ft_initiate_fds(args);
	while (lst)
	{
		if ((ft_pipe(args, lst, i) < 0) || \
			(ft_redirection(lst) < 0))
			return (-1);
		pid = fork();
		if (pid == 0)
		{
			if (0 <= ft_dup(lst, i))
			{
				execve(ft_strjoin("/bin/", lst->data[0]), lst->data, args->envp);
			}
			exit(1);
		}
		ft_close_fd(args, i);
		lst = lst->next;
		i++;
	}
	while (0 < wait(NULL))
		;
	return (0);
}