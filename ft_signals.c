/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:56:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/03 15:42:51 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_handler(int sig)
{
	if (sig == SIGINT)
		ft_get_status(getpid(), 1, 1);
	else if (sig == SIGUSR1)
		ft_get_status(getpid(), 0, 1);
	exit(1);
}

static void	ft_handler(int sig)
{
	int			st;
	pid_t		pid;
	
	st = -1;
	pid = 1;
	if (sig == SIGINT)
	{
		while (0 < pid)
		{
			pid = wait(&st);
			if ((0 < pid) && (st == 2))
				ft_get_status(pid, 130, 1);
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (st == -1)
			rl_redisplay();
		ft_get_status(getpid(), 1, 1);
	}
}

void	ft_signals(int sig)
{
	if (!sig)	
		signal(SIGINT, ft_handler);
	else if (sig)
	{
		signal(SIGINT, ft_heredoc_handler);
		signal(SIGUSR1, ft_heredoc_handler);
	}
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}