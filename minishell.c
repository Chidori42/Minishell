/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/14 20:33:30 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_proced_process(t_pars *args)
{
	int			st;

	st = 1;
	g_sig = 0;
	if (args)
	{
		if (!isatty(0))
			(perror(""), exit(0));
		args->tab = NULL;
		args->input = ft_inject_space(args->input);
		if (!ft_split_input(&args->tab, args->input))
		{
			if (!ft_parse(args, args->tab))
			{
				if (!ft_create_list(args, args->tab) && \
					!ft_expander(args, args->lst))
					ft_executer(args);
				ft_free_list(args->lst);
			}
			ft_free_2_dm(args->tab);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pars		args;

	(void)av;
	ft_signals(0);
	if (ac == 1)
	{
		args.ext_st = 0;
		ft_set_env(&args, envp);
		ft_get_status(0, &args.ext_st, 0, 100);
		while (true)
		{
			args.input = readline("Minishell: ");
			if (!args.input)
				break ;
			if (args.input && args.input[0])
			{
				add_history(args.input);
				ft_proced_process(&args);
			}
			free (args.input);
		}
		ft_close(&args);
	}
	return (0);
}
