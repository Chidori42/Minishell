/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:07:27 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/20 12:27:43 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_pipe(int *p)
{
	if (p)
	{
		if ((close (p[0]) < 0) || (close (p[1]) < 0))
			ft_putendl_fd(strerror(errno), 2);
	}
}

static int	ft_generate_name(char **name)
{
	int			i;
	char		*tmp;

	i = 1;
	*name = ft_strdup("pipe");
	if (!*name)
		return (ft_putendl_fd(strerror(errno), 2), -1);
	while (!access(*name, F_OK))
	{
		tmp = *name;
		*name = ft_strjoin("pipe_", ft_itoa(i));
		if (!*name)
			return (ft_putendl_fd(strerror(errno), 2), -1);
		free (tmp);
		i++;
	}
	return (0);
}

static int	ft_pipe_file(int *tab)
{
	char		*pipe;

	pipe = NULL;
	if (tab && !ft_generate_name(&pipe))
	{
		tab[0] = open(pipe, O_CREAT | O_TRUNC, 0666);
		if ((tab[0] < 0))
			return (free(pipe), \
				ft_putendl_fd(strerror(errno), 2), -1);
		tab[1] = open(pipe, O_WRONLY, 0222);
		if ((tab[1] < 0) && !close(tab[0]))
		{
			unlink(pipe);
			return (free(pipe), \
				ft_putendl_fd(strerror(errno), 2), -1);
		}
		unlink(pipe);
	}
	return (free(pipe), 0);
}

static int ft_read(t_pars *ags, char *buf, char *lm, char *rf, int *fds)
{
	pid_t			pid;
	int				ext_st;

	if ((pid = fork()) < 0)
		return(ft_putendl_fd(strerror(errno), 2), -1);
	else if (pid == 0)
	{
		ft_heredoc_signals();
		buf= ft_strdup("");
		while (true)
		{
			free (buf);
			buf= readline("> ");
			if (!buf|| !ft_strcmp(buf, lm))
				kill(getpid(), SIGUSR1);
			if (!ft_is_there_quotes(rf))
				ft_expander(ags, &buf);
			buf= ft_strs_join(buf, ft_strdup("\n"));
			ft_putstr_fd(buf, fds[1]);
		}
	}
	waitpid(pid, &ext_st, 0);
	if (ext_st <= 128 || close(fds[1]) < 0)
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (free(buf), 0);
}

int	ft_heredoc(t_pars *ags, char *lm, char *rf, int *fd)
	{
	int		fds[2];
	char	*buf;

	fds[0] = -1;
	if (0 <= ft_pipe_file(fds) && lm)
	{
		*fd = fds[0];
		buf = (char *)malloc(sizeof(char) * 10);
		if (buf)
		{
			if (!ft_read(ags, buf, lm, rf, fds))
				return (fds[0]);
		}
		ft_close_pipe(fds);
	}
	return (-1);
}
