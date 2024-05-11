/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/06 22:27:40 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dup_fd(int new, int old, int *st)
{
	if ((2 < new) && dup2(new, old) < 0)
		return (ft_putendl_fd(strerror(errno), 2), \
			(*st = 1), -1);
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

int	ft_get_status(pid_t new_pid, int *cont, int vl, int lvl)
{
	static int		*old;
	static int		old_lvl;
	static pid_t	old_pid;

	if (lvl == 100)
		old = cont;
	else if ((old_lvl != lvl) || \
		((old_lvl == lvl) && (old_pid <= new_pid)))
	{
		old_pid = new_pid;
		old_lvl = lvl;
		*old = vl;
	}
	return (*old);
}

void	ft_parse_error(char *str)
{
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	free (str);
	ft_get_status(0, NULL, 258, 1);
}
