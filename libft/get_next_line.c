/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:27:09 by bramzil           #+#    #+#             */
/*   Updated: 2024/01/18 12:44:50 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_rst(char **str, int fd)
{
	if (0 < fd && fd <= OPEN_MAX)
	{
		free (*str);
		*str = NULL;
	}
}

static char	*ft_substring_part(char *rst, char *buf, size_t bf_len)
{
	size_t			len;
	char			*line;

	len = ft_strllen(buf, '\n');
	line = ft_calloc((len + 1), 1);
	if (!line)
		return (NULL);
	ft_bzero(line, len);
	ft_memcpy(line, buf, len);
	line[len] = '\0';
	if (ft_strllen(buf, '\n') < bf_len)
	{
		len = bf_len - ft_strllen(buf, '\n');
		ft_bzero(rst, len);
		ft_memcpy(rst, (buf + ft_strllen(buf, '\n')), len);
	}
	return (line);
}

static char	*ft_substring(char **rst, char *buf, size_t bf_len)
{
	char		*line;

	if (!buf)
		return (NULL);
	else if (!bf_len)
		return (free(buf), NULL);
	else if (ft_strchar(buf, '\n'))
	{
		line = ft_substring_part(*rst, buf, bf_len);
		if (!line)
			return (free(buf), free(*rst), *rst = NULL, NULL);
	}
	else
	{
		line = ft_calloc((bf_len + 1), 1);
		if (!line)
			return (free(buf), NULL);
		ft_memcpy(line, buf, bf_len);
	}
	line[bf_len] = '\0';
	return (free(buf), line);
}

static char	*ft_realloc(char *ptr, size_t bf_len, size_t bf_sz)
{
	char		*rtn;

	rtn = NULL;
	if (!ptr && bf_sz)
	{
		rtn = ft_calloc((bf_sz + 1), 1);
		if (!rtn)
			return (NULL);
	}
	else if (ptr)
	{
		if (!bf_len)
			bf_len = ft_strllen(ptr, '\0');
		rtn = ft_calloc((bf_len + bf_sz + 1), 1);
		if (!rtn)
			return (free(ptr), NULL);
		rtn[bf_len] = '\0';
		ft_bzero((rtn + bf_len), bf_sz);
		ft_memcpy(rtn, ptr, bf_len);
		free (ptr);
	}
	return (rtn);
}

char	*get_next_line(int fd)
{
	static char		*rst[OPEN_MAX];
	char			*buf;
	size_t			bf_len;
	int				rb;

	if ((read(fd, 0, 0) < 0) || (BUFFER_SIZE < 0) || (INT_MAX < BUFFER_SIZE))
		return (free_rst(&rst[fd], fd), NULL);
	buf = rst[fd];
	rst[fd] = NULL;
	rb = 1;
	bf_len = ft_strllen(buf, '\0');
	while (!ft_strchar(buf, '\n') && rb)
	{
		buf = ft_realloc(buf, bf_len, BUFFER_SIZE);
		if (!buf)
			return (free(rst[fd]), rst[fd] = NULL, NULL);
		rb = read(fd, (buf + bf_len), BUFFER_SIZE);
		bf_len += rb;
	}
	if (ft_strchar(buf, '\n') && (bf_len - ft_strllen(buf, '\n')))
		rst[fd] = ft_calloc((bf_len - ft_strllen(buf, '\n') + 1), 1);
	if (ft_strchr(buf, '\n') && (bf_len - ft_strllen(buf, '\n')) && !rst[fd])
		return (free(buf), NULL);
	return (ft_substring(&rst[fd], buf, bf_len));
}
