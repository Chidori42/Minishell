/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:40:30 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/21 18:06:27 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data 	arg;

void    hundler(int sig)
{
    if (sig == SIGUSR1)
	{
		rl_clear_history();
		free(arg.str);
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

char	**join_env(t_data *arg, char **p)
{
	int i;

	i = 0;
	while (p[i])
	{
		arg->tmp = ft_strjoin(arg->tmp, p[i]);
		arg->tmp = ft_strjoin(arg->tmp, "\n");
		if (!arg->tmp)
			return (NULL);
		i++;
	}
	return (ft_split(arg->tmp, '\n'));
}

int main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	arg.pid = getpid();
	set_parameter(&arg);
	arg.envp = join_env(&arg, env);
	if (!arg.envp)
		return (-1);
	signal(SIGUSR1, hundler);
	signal(SIGINT, hundler);
	while(1)
	{
	// system("leaks minishell");
		arg.str = readline("Minishel > ");
		if (arg.str == NULL || arg.str[0] == '\0')
		{
			if (arg.str == NULL)
			{
				kill(arg.pid, SIGUSR1);
				break ;
			}
			else
				kill(arg.pid, SIGINT);
			free(arg.str);
		}
		else
		{
			add_history(arg.str);
			parcing(&arg);
			ft_builthing(&arg);
		}
		free(arg.str);
	}
}
