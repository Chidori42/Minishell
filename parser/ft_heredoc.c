/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:07:27 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/12 01:52:50 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_generate_name(char **name)
{
	int			i;
	char		*tmp;

	i = 1;
	*name = ft_strdup("/tmp/pipe");
	if (!*name)
		return (ft_putendl_fd(strerror(errno), 2), -1);
	while (!access(*name, F_OK))
	{
		tmp = *name;
		*name = ft_strs_join(ft_strdup("/tmp/pipe_"), ft_itoa(i));
		if (!*name)
			return (ft_putendl_fd(strerror(errno), 2), -1);
		free (tmp);
		i++;
	}
	return (0);
}

static int	ft_pipe_file(char **path, int *tab)
{
	char		*pipe;

	pipe = NULL;
	*path = NULL;
	if (tab && !ft_generate_name(&pipe))
	{
		tab[0] = open(pipe, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if ((tab[0] < 0))
			return (free(pipe), \
				ft_putendl_fd(strerror(errno), 2), -1);
		*path = pipe;
	}
	return (0);
}

static void	ft_child(t_pars *ags, char *lim, int fd, int qt)
{
	char	**buf;

	ft_signals(1);
	rl_catch_signals = 1;
	buf = (char **)malloc(sizeof(char *) * 2);
	if (!buf)
		exit(1);
	buf[1] = NULL;
	while (true)
	{
		buf[0] = readline("> ");
		if (!buf[0] || !ft_strcmp(buf[0], lim))
			break ;
		if (qt && ags && buf)
			ft_expand_cmd(ags, &buf, 0);
		buf[0] = ft_strs_join(buf[0], ft_strdup("\n"));
		ft_putstr_fd(buf[0], fd);
		free (buf[0]);
	}
	exit(0);
}

static int	ft_read(t_pars *ags, char *lim, int fd, int qt)
{
	pid_t			pid;
	int				ext_st;

	ext_st = 1;
	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd(strerror(errno), 2), -1);
	else if (pid == 0)
		ft_child(ags, lim, fd, qt);
	waitpid(pid, &ext_st, 0);
	if ((close(fd) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	if (WIFSIGNALED(ext_st))
		return (WTERMSIG(ext_st));
	return (ext_st);
}

int	ft_heredoc(t_pars *args, char **lim)
{
	int		qt;
	int		fd;
	int		st;
	char	*tmp;

	qt = 1;
	st = 0;
	fd = -1;
	tmp = *lim;
	if (lim && (ft_pipe_file(lim, &fd) < 0))
		return (1);
	if (ft_is_there_quotes(tmp))
	{
		tmp = ft_remove_qts(tmp);
		qt = 0;
	}
	st = ft_read(args, tmp, fd, qt);
	ft_get_status(0, NULL, st, 1);
	free(tmp);
	return (st);
}
