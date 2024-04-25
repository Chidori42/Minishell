/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/25 02:01:33 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_sig;

static void	ft_proced_process(t_pars *args)
{
	int			st;
	
	st = 1;
	args->tab = NULL;
	args->input = ft_inject_space(args->input);
	if (!ft_split_input(&args->tab, args->input))
	{
		st = ft_check_parse(args, args->tab);
		if (!st)
		{
			g_sig = 1;
			if (args->tab)
			{
				st = ft_create_list(args, args->tab);
				if (!st)
					st = ft_execute_lst(args);
				ft_free_list(args->lst);
			}
		}
		ft_free_2_dm(args->tab);
	}
	args->ext_st = st;
}

int main(int ac, char **av, char **envp)
{
	(void)		av;
	t_pars		args;
	
	ft_parent_signals();
	if (ac == 1)
	{
		args.ext_st = 0;
		ft_set_env(&args, envp);
		while (true)
		{	
			g_sig = 0;
			args.input = readline("prompt: ");
			if (!args.input)
				kill(getpid(), SIGUSR1);
			if (args.input && args.input[0])
			{
				add_history(args.input);
				ft_proced_process(&args);
			}
			free (args.input);
			system("leaks	minishell");
		}
	}
	return (0);
}
