/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 10:54:00 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_sig;

// void	f(void)
// {
// 	// system("lsof minishell > file");
// 	system("leaks minishell");
// }

int	main(int ac, char **av, char **envp)
{
	t_pars		args;

	(void) av;
	ft_parent_signals();
	if (ac == 1)
	{
		args.envp = ft_dup_env(envp, NULL);
		while (true)
		{
			g_sig = 0;
			args.input = readline("prompt: ");
			if (!args.input || !ft_strcmp("exit", args.input))
				kill(getpid(), SIGUSR1);
			if (args.input && args.input[0])
			{
				add_history(args.input);
				args.ext_st = ft_check_parse(&args, args.input);
				g_sig = 1;
				if (args.tab && !args.ext_st)
					ft_execution(&args);
				else if (args.tab)
					ft_free_2_dm(args.tab);
			}
			else if (args.input)
				free (args.input);
		}
	}
	return (0);
}
