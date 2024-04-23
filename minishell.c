/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 04:10:42 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_sig;

static void	ft_proced_process(t_pars *args)
{
	args->tab = NULL;
	args->ext_st = ft_check_parse(args, args->input);
	if (args->ext_st != 258)
	{
		g_sig = 1;
		if (args->tab && !args->ext_st)
			ft_execution(args);
		else if (args->tab)
			ft_free_2_dm(args->tab);
	}
}

int main(int ac, char **av, char **envp)
{
	(void)		av;
	t_pars		args;
	
	ft_parent_signals();
	if (ac == 1)
	{
		ft_set_env(&args, envp);
		while (true)
		{	
			g_sig = 0;
			args.input = readline("prompt: ");
			if (!args.input || !ft_strcmp("exit", args.input))
				kill(getpid(), SIGUSR1);
			if (args.input && args.input[0])
			{
				add_history(args.input);
				ft_proced_process(&args);
			}
			else if (args.input)
				free (args.input);
		}
	}
	return (0);
}
