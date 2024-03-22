/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:56:04 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/18 22:21:36 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int simple_fnmatch(char *pattern, char *string)
{
    if (*pattern == '\0' && *string == '\0')
        return 0;
    if (*pattern == '*')
    {
        if (*(pattern + 1) != '\0' && *string == '\0')
            return -1;
        if (simple_fnmatch(pattern + 1, string) == 0
            || simple_fnmatch(pattern, string + 1) == 0)
            return 0;
    }
    if (*pattern == '?' || *pattern == *string)
        return simple_fnmatch(pattern + 1, string + 1);
    return -1;
}

char    *get_current_dir(char *p)
{
    struct dirent   *entry;
    char            *file = NULL;
    DIR             *tmp;

    tmp = opendir(".");
    if (!tmp)
    {
        perror("Unable to open current directory");
        exit(EXIT_FAILURE);
    }
    while(((entry = readdir(tmp)) != NULL))
    {
        if (entry->d_name[0] == '.')
            continue;
        if (simple_fnmatch(p , entry->d_name) == 0)
        {
            file = ft_strjoin(file, entry->d_name);
            file = ft_strjoin(file, " ");
        }

    }
    closedir(tmp);
    return (file);
}

char    *ft_wildcard(char *str)
{
    int     i;
    int     j;
    char    *files;
    char    *tmp;

    i = 0;
    files = get_current_dir(str);
    return (files);
}

int main()
{
    char *p;
    p = ft_wildcard("ft*p*.c");
    if (!p)
        printf("NULL");
    printf("%s\n", p);
}