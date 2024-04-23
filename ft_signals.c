/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:56:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 05:28:30 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_sig;

static void	ft_parent_handler(int sig)
{
	if (sig == SIGUSR1)
		exit(0);
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_sig)
			rl_redisplay();
	}
}

void	ft_parent_signals()
{
	signal(SIGINT, ft_parent_handler);
	signal(SIGUSR1, ft_parent_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}

static void	ft_heredoc_handler(int sig)
{
	if (sig == SIGUSR1)
		exit(129);
	else if (sig == SIGINT)
		exit (128);
	else if (sig == SIGQUIT)
		exit(0);
	exit(0);
}

void	ft_heredoc_signals()
{
	signal(SIGINT, ft_heredoc_handler);
	signal(SIGUSR1, ft_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}