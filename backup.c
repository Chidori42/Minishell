/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:27:15 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 10:13:13 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_red_left(char *s, int i)
{
	while (i && s[--i])
	{
		if ((s[i] < 9 || 13 < s[i]) && s[i] != 32)
		{
			if (s[i] == '>' || s[i] == '<')
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

int	ft_check_redir_out(char *s, int *i)
{
	if (s[*i] == '>' && s[*i + 1] == '>' && \
		s[*i + 2] == '&')
	{
		if (ft_check_red_left(s, *i))
			return (ft_parse_error(ft_substr(s, *i, 3)), -1);
		*i += 2;
	}
	else if (s[*i] == '>' && (s[*i + 1] == '|' || \
		s[*i + 1] == '&' || s[*i + 1] == '>'))
	{
		if (ft_check_red_left(s, *i))
			return (ft_parse_error(ft_substr(s, *i, 2)), -1);
		(*i)++;
	}
	else if (s[*i] == '>' && ft_check_red_left(s, *i))
		return (ft_parse_error(ft_substr(s, *i, 1)), -1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_red_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:18:39 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/16 18:15:48 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_red_left(char *s, int i)
{
	while (i && s[--i])
	{
		if ((s[i] < 9 || 13 < s[i]) && s[i] != 32)
		{
			if (s[i] == '>' || s[i] == '<')
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

int	ft_check_redir_in(char *s, int *i)
{
	if (s[*i] == '<' && s[*i + 1] == '<' && \
		s[*i + 2] == '<')
	{
		if (ft_check_red_left(s, *i))
			return (ft_parse_error(ft_substr(s, *i, 3)), -1);
		*i += 2;
	}
	else if (s[*i] == '<' && (s[*i + 1] == '<' || \
		s[*i + 1] == '>'))
	{
		if (ft_check_red_left(s, *i))
			return (ft_parse_error(ft_substr(s, *i, 2)), -1);
		*i += 1;
	}
	else if (s[*i] == '<' && ft_check_red_left(s, *i))
		return (ft_parse_error(ft_substr(s, *i, 1)), -1);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flu_ct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:17:30 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/16 18:07:43 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_flu_left(char *s, int i)
{
	while (i && s[--i])
	{
		if ((s[i] < 9 || 13 < s[i]) && s[i] != 32)
		{
			if (s[i] == '|' || s[i] == '&' || s[i] == '<' || \
				s[i] == '>')
				return (1);
			else
				return (0);
		} 
	}
	return (1);
}

int	ft_check_flu_ct(char *s, int *i)
{
	if ((s[*i] == '|' && s[*i + 1] == '|') || \
		(s[*i] == '&' && s[*i + 1] == '&') || \
		(s[*i] == '|' && s[*i + 1] == '&') || \
		(s[*i] == '&' && s[*i + 1] == '|')
		)
	{
		if (ft_check_flu_left(s, *i))
			return (ft_parse_error(ft_substr(s, *i, 2)), -1);
		(*i)++;
	}
	else if ((s[*i] == '|' || s[*i] == '&'))
	{
		if (ft_check_flu_left(s, *i))
			return (ft_parse_error(ft_substr(s, *i, 1)), -1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inject_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:06:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/22 17:16:41 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_operator(char *s, int i)
{
	if ((s[i] == '|' && s[i + 1] == '|') || \
		(s[i] == '&' && s[i + 1] == '&'))
		return (2);
	else if (s[i] == '|')
		return (1);
	return (0);
}

static int	ft_word_len(char *s, int *i)
{
	int			l;

	l = *i;
	while (s && s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			*i = ft_scape_quotes(s, *i);
		else if (s[*i] == '(')
			*i = ft_scape_parenth(s, *i);
		else if (ft_is_operator(s, *i))
			break ;
		else
			(*i)++;
	}
	return (*i - l);
}

// static int	ft_spaces_needed(char *str)
// {
// 	int			i;
// 	int			nb;
// 	char		qt;

// 	i = -1;
// 	nb = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 		{
// 			qt = str[i];	
// 			while (str[i] != qt)
// 				i++;
// 		}
// 		if (!ft_is_operator(str[i]) && str[i - 1] != ' ' && \
// 			str[i - 1] != str[i])
// 			nb += 1;
// 		if (!ft_is_operator(str[i]) && str[i + 1] != ' ' && \
// 			str[i + 1] != str[i])
// 			nb += 1;
// 	}
// 	return (nb);
// }

// static int	ft_add_spaces(char *input, char *str, int i, int j)
// {
// 	int			b;

// 	b = 0;
// 	if (!ft_is_operator(input[i]) && \
// 		input[i - 1] != ' ' && input[i - 1] != input[i] && ++b)
// 	{
// 		str[++j] = ' ';
// 		str[++j] = input[i];
// 	}
// 	if (!ft_is_operator(input[i]) && \
// 		input[i + 1] != ' ' && input[i + 1] != input[i] && ++b)
// 	{
// 		if (b == 1)
// 			str[++j] = input[i];
// 		str[++j] = ' ';
// 	}
// 	if (!b)
// 		str[++j] = input[i];
// 	return (j);
// }

char	*ft_inject_space(char *input)
{
	int			i;
	int			j;
	char		qt;
	char		*str;

	i = -1;
	j = -1;
	str = (char *)malloc(sizeof(char) * (ft_strlen(input + \
		ft_spaces_needed(input) + 1)));
	if (str)
	{
		while (str && input[++i])
		{
			if(input[i] == '\'' || input[i] == '\"')
			{
				qt = input[i];
				str[++j] = input[i];
				while(input[++i] != qt)
					str[++j] = input[i];
			}
			j = ft_add_spaces(input, str, i, j);
		}
		str[++j] = '\0';
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_paren.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:53:13 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/22 18:17:37 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_scape_parenth(char *input, int i)
{
	int			nb;

	nb = 1;
	while (input && input[++i] && nb)
	{
		if (input[i] == '(')
			nb++;
		else if (input[i] == ')')
			nb--;
	}
	return (i);
}

int	ft_check_parenthesis(char *s)
{
	int			i;
	int			nb;

	i = -1;
	nb = 0;
	while (s && s[++i])
	{
		if (s[i] == '(')
			nb++;
		else if (s[i] == ')')
		{
			if (!nb)
				return (ft_parse_error(")"), 0);
			else
				nb--;
		}
	}
	return (nb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_complet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:55:04 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/04 03:10:45 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_check_frst(char *input)
{
	if (input && (input[0] == '|' || \
		input[0] == '&' || input[0] == ')'))
		return (ft_parse_error(ft_substr(input, 0, 1)), -1);
	return (0);
}

char	*ft_is_complet(char *prmt)
{
	char 		*tmp;
	char 		*input;

	input = NULL;
	if (!prmt)
		prmt = "prompt: ";
	tmp = readline (prmt);
	if (tmp == NULL || !ft_strcmp("exit", tmp))
		kill(getpid(), SIGUSR1);
	input = ft_strs_join(input, tmp);
	add_history(input);
	if ((ft_check_frst(input) < 0) || \
		(ft_check_parse(input) < 0))
		return (free(input), NULL);
	else if (ft_check_last(input) == 1)
		ft_is_complet("> ");
	return (input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inject_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:06:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/20 14:26:09 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_operator(char *s, int i)
{
	if (s)
	{	
		if (s[i] == '|' || s[i] == '<' || \
			s[i] == '>')
			return (1);
	}
	return (0);
}

static int	ft_word_len(char *s, int *i)
{
	int			l;

	if ((l = ft_is_operator(s, *i)) == 0)
	{
		l = *i;
		while (s && s[*i])
		{
			if (s[*i] == '\'' || s[*i] == '\"')
				*i = ft_scape_quotes(s, *i);
			else if (ft_is_operator(s, *i))
				break ;
			else
				(*i)++;
		}
		return (*i - l);
	}
	*i += l;
	return (l);
}

char	*ft_inject_space(char *input)
{
	int			i;
	int			j;
	int			w_len;
	char		*str;

	j = 0;
	i = 0;
	str = ft_strdup("");
	while (input && input[i])
	{
		w_len = ft_word_len(input, &i);
		if (w_len)
		{
			str = ft_strs_join(str, ft_substr(input, j, w_len));
			str = ft_strs_join(str, ft_strdup(" "));
			j += w_len;
		}
	}
	return (free (input), str);
}