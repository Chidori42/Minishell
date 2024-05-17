/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:56:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/14 20:33:34 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_heredoc_handler(int sig)
{
	int			st;

	st = -1;
	if (sig == SIGINT)
		exit(1);
}

static void	ft_quit_handler(int sig)
{
	int						st;
	pid_t					pid;

	if (sig == SIGQUIT)
	{
		pid = wait(&st);
		if (0 < pid)
		{
			g_sig = 3;
			ft_get_status(pid, NULL, 128 + st, 3);
			write(1, "Quit: 3\n", 9);
		}
	}
}

static void	ft_int_handler(int sig)
{
	int			st;
	pid_t		pid;

	st = -1;
	if (sig == SIGINT && ++g_sig)
	{
		pid = wait(&st);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (pid != -1)
			ft_get_status(pid, NULL, 128 + st, 3);
		else
			(rl_redisplay(), \
				ft_get_status(0, NULL, 1, 0));
	}
}

void	ft_signals(int sig)
{
	if (!sig)
	{
		signal(SIGINT, ft_int_handler);
		signal(SIGQUIT, ft_quit_handler);
	}
	else if (sig)
	{
		signal(SIGINT, ft_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	RL_SIG = 0;
}
