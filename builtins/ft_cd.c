/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:16:01 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/07 01:32:55 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_getdes(t_pars *args, char *des)
{
	char		*new_des;

	if (!des)
		new_des = ft_getenv(args->envp, "HOME");
	else
		new_des = ft_strdup(des);
	return (new_des);
}

int	ft_setoldpwd(t_pars *args, t_cmd *node)
{
	char		**tmp;

	tmp = ft_split("export tmp", ' ');
	if (!tmp)
		return (-1);
	free(tmp[1]);
	tmp[1] = ft_strs_join(ft_strdup("OLDPWD="), \
		ft_getenv(args->envp, "PWD"));
	if (!tmp[1])
		return (ft_free_2_dm(tmp), -1);
	ft_export(args, node, tmp);
	return (ft_free_2_dm(tmp), 0);
}

int	ft_setcwd(t_pars *args, t_cmd *node, int *ref, char *cwd)
{
	char			*ptr;
	char			**tmp;

	ptr = ft_getcwd(args);
	if (!ptr)
		ptr = args->cwd;
	tmp = ft_split("export tmp", ' ');
	if (!tmp)
		return (-1);
	if (!ft_setoldpwd(args, node))
	{
		if (cwd)
			(*ref)++;
		free(tmp[1]);
		tmp[1] = ft_strs_join(ft_strdup("PWD="), \
			ft_strs_join(ft_strdup(ptr), cwd));
		if (!tmp[1])
			return (ft_free_2_dm(tmp), -1);
		if (!ft_export(args, node, tmp))
		{
			free(args->cwd);
			args->cwd = ft_getenv(args->envp, "PWD");
		}
	}
	return (ft_free_2_dm(tmp), 0);
}

int	ft_cd(t_pars *args, t_cmd *node)
{
	char			*des;
	static int		ref;

	des = ft_getdes(args, node->data[1]);
	if (args && node)
	{
		if (0 <= chdir(des))
		{
			if (!ft_getcwd(args) && !ft_strcmp(des, "."))
				ft_setcwd(args, node, &ref, ft_strdup("/."));
			else if (!ft_getcwd(args) && !ft_strcmp(des, ".."))
				ft_setcwd(args, node, &ref, ft_strdup("/.."));
			else if (ft_getcwd(args))
				(ft_setcwd(args, node, NULL, NULL), (ref = 0));
		}
		else
			return (ft_builts_error("cd", node->data[1], \
				strerror(errno)), free(des), (ref = 0), 1);
		if (ref)
			ft_cd_error();
	}
	return (free(des), 0);
}
