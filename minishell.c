/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/28 06:52:15 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_proced_process(t_pars *args)
{
	int			st;
	
	st = 1;
	args->tab = NULL;
	args->input = ft_inject_space(args->input);
	if (!ft_split_input(&args->tab, args->input))
	{
		if (!ft_check_parse(args, args->tab))
		{
			if (args->tab)
			{
				if (!ft_create_list(args, args->tab))
					ft_execute_lst(args);
				ft_free_list(args->lst);
			}
		}
		ft_free_2_dm(args->tab);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pars		args;
	(void)		av;
	
	if (ac == 1)
	{
		ft_signals(0);
		ft_set_env(&args, envp);
		while (true)
		{
			//system("leaks minishell");
			args.input = readline("Minishell: ");
			if (!args.input)
				kill(getpid(), SIGUSR1);
			if (args.input && args.input[0])
			{
				add_history(args.input);
				ft_proced_process(&args);
			}
			args.ext_st = ft_get_exit_status(0, 0);
			free (args.input);
		}
	}
	return (0);
}
