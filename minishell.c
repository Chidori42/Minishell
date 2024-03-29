/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:47:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/29 11:31:33 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    hundler(int sig)
{
    if (sig == SIGUSR1)
	{
		rl_clear_history();
		exit(0);
	}
    else if (sig == SIGINT)
	{
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
	// else if (sig == SIGQUIT)
	// 	return ;
}

void	send_segnal(t_pars *args, char *str)
{
	if (str == NULL || str[0] == '\0' || str[0] == '\n')
	{
		if (str == NULL)
			kill(args->pid, SIGUSR1);
		else
			kill(args->pid, SIGINT);
	}
}

int main(int ac, char **av, char **envp)
{
	t_pars		args;
	t_cmd		*tmp;
	(void)ac;
	(void)av;
	
	args.envp = envp;
	args.pid = getpid();
	signal(SIGUSR1, hundler);
	signal(SIGINT, hundler);
	while (true)
	{	
		args.input = ft_is_complet();
		send_segnal(&args, args.input);
		add_history(args.input);
		args.input = ft_inject_space(args.input);
		args.tab = ft_split_input(args.input);
		args.lst = ft_create_list(args.tab);
		tmp = args.lst;
		ft_builthing(tmp, &args);
		ft_execute_lst(&args);
	}
	return (0);
}
