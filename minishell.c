/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/07 23:15:13 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hundler(int sig)
{
	if (sig == SIGUSR1)
		exit(0);
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

void	check_execute(t_cmd *cmds, t_pars *args)
{
	while (cmds)
	{
		if (!ft_strcmp(cmds->data[0], "export") || !ft_strcmp(cmds->data[0], "echo")
			|| !ft_strcmp(cmds->data[0], "cd") || !ft_strcmp(cmds->data[0], "unset")
			|| !ft_strcmp(cmds->data[0], "pwd") || !ft_strcmp(cmds->data[0], "exit"))
		{
			ft_builthing(cmds, args);
		}
		else
		{
			ft_execute_lst(args);
		}
		cmds = cmds->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pars		args;

	(void)av;
	(void)ac;
	args.envp = ft_dup_env(envp, NULL);
	signal(SIGINT, hundler);
	signal(SIGQUIT, hundler);
	rl_catch_signals = 0;
	while (true)
	{
		args.input = ft_is_complet();
		if (args.input == NULL)
			kill(args.pid, SIGUSR1);
		if (args.input)
		{
			args.input = ft_inject_space(args.input);
			args.tab = ft_split_input(args.input);
			ft_expander(args.tab);
			args.lst = ft_create_list(&args, args.tab);
			ft_remove_quotes(args.lst);
			check_execute(args.lst, &args);
			(ft_free_list(args.lst), ft_free_2_dm(args.tab));
			(free (args.input), args.input = NULL);
		}
	}
	return (0);
}
