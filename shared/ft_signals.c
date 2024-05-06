/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:56:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/06 03:29:19 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_handler(int sig)
{
	(void)sig;
}

static void	ft_heredoc_handler(int sig)
{
	if (sig == SIGINT)
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
		pid = wait(&st);
		if (pid != 1)
			ft_get_status(pid, 128 + st, 1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (st == -1)
			(rl_redisplay(), \
				ft_get_status(0, 1, 1));
	}
	else if (sig == SIGQUIT)
		if (0 < wait(NULL))
			printf("Quit: 3\n");
}

void	ft_signals(int sig)
{
	if (!sig)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, ft_handler);
	}
	else if (sig)
	{
		signal(SIGINT, ft_heredoc_handler);
		signal(SIGUSR1, ft_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	RL_SIG = 0;
}
