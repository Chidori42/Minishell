/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeltif <abdeltif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:40:30 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/25 08:12:27 by abdeltif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data 	arg;

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

char	**join_env(char **p)
{
	int		i;
	char	**res;
	char	*new_str;

	i = 0;
	new_str = NULL;
	while (p[i])
	{
		new_str = ft_strjoin(new_str, p[i]);
		new_str = ft_strjoin(new_str, "\n");
		if (!new_str)
			return (NULL);
		i++;
	}
	res = ft_split(new_str, '\n');
	if (!res)
		return (NULL);
	free(new_str);
	return (res);
}

int main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	arg.pid = getpid();
	set_parameter(&arg);
	arg.envp = join_env(env);
	if (!arg.envp)
		return (-1);
	signal(SIGUSR1, hundler);
	signal(SIGINT, hundler);
	while(1)
	{
		//system("leaks minishell");
		arg.str = readline("Minishel > ");
		if (arg.str == NULL || arg.str[0] == '\0' || arg.str[0] == '\n')
		{
			if (arg.str == NULL)
			{
				kill(arg.pid, SIGUSR1);
				break ;
			}
			else
				kill(arg.pid, SIGINT);
		}
		else
		{
			add_history(arg.str);
			parcing(&arg);
			ft_expand(&arg, arg.cmds);
			ft_builthing(&arg);
		}
		free(arg.str);
	}
}
