/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:07:27 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/24 23:01:39 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_sig;

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

static void ft_child(t_pars *ags, char *lim, int fd, int qt)
{
	char	 **buf;
	
	ft_heredoc_signals();
	buf = (char **)malloc(sizeof(char *) * 2);
	if (!buf)
		exit(1);
	while (true)
	{
		buf[0] = readline("> ");
		if (!buf[0])
				kill(getpid(), SIGUSR1);
		if (!buf[0]|| !ft_strcmp(buf[0], lim))
			break;
		if (qt)
			ft_expander(ags, buf);
		buf[0] = ft_strs_join(buf[0], ft_strdup("\n"));
		ft_putstr_fd(buf[0], fd);
		free (buf[0]);
	}
	exit(0);
}

static int ft_read(t_pars *ags, char *lim, int fd, int qt)
{
	pid_t			pid;
	int				ext_st;

	if ((pid = fork()) < 0)
		return(ft_putendl_fd(strerror(errno), 2), -1);
	else if (pid == 0)
		ft_child(ags, lim, fd, qt);
	waitpid(pid, &ext_st, 0);
	if ((close(fd) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (ext_st);
}

char	*ft_heredoc(t_pars *ags, char *lm)
{
	int		qt;
	int		fd;
	char	*path;

	qt = 1;
	fd = -1;
	if (lm && (0 <= ft_pipe_file(&path, &fd)))
	{
		if (ft_is_there_quotes(lm))
		{
			lm = ft_remove_qts(lm);
			qt = 0;
		}
		if (!ft_read(ags, lm, fd, qt))
			return (free(lm), path);
	}
	return (free(lm), NULL);
}
