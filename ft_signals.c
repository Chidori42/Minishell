/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:56:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/28 01:46:56 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_handler(int sig)
{
	if (sig == SIGINT)
		ft_get_exit_status(1, 1);
	else if (sig == SIGUSR1)
		ft_get_exit_status(0, 1);
	exit(1);
}

static void	ft_parent_handler(int sig)
{
	int			st;
	
	st = -1;
	if (sig == SIGUSR1)
	{
		ft_get_exit_status(0, 1);
		exit(1);
	}
	else if (sig == SIGINT)
	{
		g_sig = 1;
		ft_get_exit_status(1, 1);
		while (wait(&st) != -1)
			;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (st == -1)
			rl_redisplay();
	}
}

void	ft_signals(int sig)
{
	if (!sig)
	{	
		signal(SIGINT, ft_parent_handler);
		signal(SIGUSR1, ft_parent_handler);
	}
	else if (sig)
	{
		signal(SIGINT, ft_heredoc_handler);
		signal(SIGUSR1, ft_heredoc_handler);
	}
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}