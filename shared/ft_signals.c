/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:56:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/06 22:36:15 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_handler(int sig)
{
	(void)sig;
}

static void	ft_heredoc_handler(int sig)
{
	int			st;
	
	st = -1;
	if (sig == SIGINT)
		exit(1);
}

static void	ft_quit_handler(int sig)
{
	int			st;
	pid_t 		pid;
	
	if (sig == SIGQUIT)
	{
		pid = wait(&st);
		if (0 < pid && ++G_sig)
		{
			ft_get_status(pid, NULL, 128 + st, 3);
			printf("Quit: 3\n");
		}
		else
			SIG_IGN;
	}
}

static void	ft_int_handler(int sig)
{
	int			st;
	pid_t		pid;

	st = -1;
	if (sig == SIGINT && ++G_sig)
	{
		pid = wait(&st);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (pid != -1)
			ft_get_status(pid, NULL, 128 + st, 3);
		else
			(rl_redisplay(), \
				ft_get_status(0, NULL, 1, 3));
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
