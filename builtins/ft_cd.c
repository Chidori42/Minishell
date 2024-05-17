/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:16:01 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/13 20:22:17 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_getdes(t_pars *args, char *des)
{
	char		*new_des;

	if (!des)
		new_des = ft_getenv(args->envp, ft_strdup("HOME"));
	else
		new_des = ft_strdup(des);
	return (new_des);
}

int	ft_setoldpwd(t_pars *args, t_cmd *node)
{
	char		**tmp;

	tmp = ft_split("export tmp", ' ');
	if (!tmp)
		return (chdir(args->cwd), -1);
	free(tmp[1]);
	tmp[1] = ft_strs_join(ft_strdup("OLDPWD="), \
		ft_getenv(args->envp, ft_strdup("PWD")));
	if (!tmp[1])
		return (chdir(args->cwd), ft_free_2_dm(tmp), -1);
	if (ft_export(args, node, tmp))
		return (chdir(args->cwd), ft_free_2_dm(tmp), \
			chdir(args->cwd), -1);
	return (ft_free_2_dm(tmp), 0);
}

int	ft_setcwd(t_pars *args, t_cmd *node, int *ref, char *cwd)
{
	char			*ptr;
	char			**tmp;

	(cwd && (*ref)++);
	ptr = ft_getcwd(args);
	if (!ptr)
		ptr = args->cwd;
	tmp = ft_split("export tmp", ' ');
	if (!tmp)
		return (chdir(args->cwd), -1);
	free(tmp[1]);
	tmp[1] = ft_strs_join(ft_strdup("PWD="), \
		ft_strs_join(ft_strdup(ptr), cwd));
	if (!tmp[1])
		return (chdir(args->cwd), ft_free_2_dm(tmp), -1);
	if (ft_export(args, node, tmp))
		return (chdir(args->cwd), ft_free_2_dm(tmp), -1);
	free(args->cwd);
	args->cwd = ft_getenv(args->envp, ft_strdup("PWD"));
	return (ft_free_2_dm(tmp), 0);
}

int	ft_cd(t_pars *args, t_cmd *node)
{
	char			*des;
	static int		ref;

	des = ft_getdes(args, node->data[1]);
	if (!args || !node)
		return (free(des), -1);
	if (!chdir(des) && !ft_setoldpwd(args, node))
	{
		if (!ft_getcwd(args) && !ft_strcmp(des, "."))
			ft_setcwd(args, node, &ref, ft_strdup("/."));
		else if (!ft_getcwd(args) && !ft_strcmp(des, ".."))
			ft_setcwd(args, node, &ref, ft_strdup("/.."));
		else if (ft_getcwd(args))
			(ft_setcwd(args, node, NULL, NULL), (ref = 0));
		return (ft_cd_error(ref), free(des), 0);
	}
	return (ft_builts_error("cd", node->data[1], \
		strerror(errno)), free(des), (ref = 0), 1);
}
