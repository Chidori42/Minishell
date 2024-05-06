/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/06 03:35:44 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dup_fd(int new, int old)
{
	if ((2 < new) && dup2(new, old) < 0)
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (0);
}

int	ft_close(t_pars *args)
{
	ft_free_2_dm(args->envp);
	printf("\033[AMinishell: exit\n");
	exit(0);
}

char	**ft_split_fr(char *str, char c)
{
	char		**arr;

	arr = NULL;
	if (str)
		arr = ft_split(str, c);
	return (free(str), arr);
}

int	ft_get_status(pid_t new_pid, int new, int set)
{
	int				tmp;
	static int		old;
	static pid_t	old_pid;

	tmp = old;
	if (set == 100)
		old_pid = 0;
	else if (set && ((old_pid <= new_pid) || \
		(new_pid == 0)))
	{
		old_pid = new_pid;
		old = new;
	}
	return (tmp);
}

void	ft_parse_error(char *str)
{
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	free (str);
	ft_get_status(0, 258, 1);
}
