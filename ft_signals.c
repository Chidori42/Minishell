/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:56:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/24 22:56:27 by bramzil          ###   ########.fr       */
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
		if (wait(NULL) == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			if (!g_sig)
				rl_redisplay();
			g_sig = 0;
		}
	}
}

static void	ft_heredoc_handler(int sig)
{
	if (sig == SIGUSR1 || sig == SIGINT)
		exit(258);
}

void	ft_parent_signals()
{
	signal(SIGINT, ft_parent_handler);
	signal(SIGUSR1, ft_parent_handler);
	signal(SIGQUIT, SIG_IGN);
	// rl_catch_signals = 0;
}

void	ft_heredoc_signals()
{
	signal(SIGINT, ft_heredoc_handler);
	signal(SIGUSR1, ft_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}