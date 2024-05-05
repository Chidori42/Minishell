/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/04 23:03:08 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_parse_error(char *str)
{
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	free (str);
	ft_get_status(0, 258, 1);
}

int	ft_free_2_dm(char **arr)
{
	int			i;

	i = -1;
	while (arr && arr[++i])
		free (arr[i]);
	free (arr);
	return (0);
}

char	**ft_split_fr(char *str, char c)
{
	char		**arr;

	arr = NULL;
	if (str)
		arr = ft_split(str, c);
	return (free(str), arr);
}
