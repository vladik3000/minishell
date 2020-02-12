/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:51:44 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/12 19:21:37 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordlen(const char *s)
{
	size_t i;

	i = 0;
	while (!ft_isspace(s[i]) && s[i])
		i++;
	return (i);
}

static size_t	count_words(const char *s)
{
	size_t words;

	words = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (ft_isspace(*s) && (!ft_isspace(*(s + 1)) || *(s + 1) == 0))
			words++;
		s++;
	}
	return (words);
}

static void		delete(char ***res, size_t j)
{
	while (--j > 0)
		ft_strdel(&(*res)[j]);
	free(*res);
	*res = NULL;
}

static char		**alloc_and_fill(const char *s, char **res)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			if (!(res[j] = ft_strsub(s, i, wordlen(s + i))))
			{
				delete(&res, j);
				return (NULL);
			}
			j++;
			i += wordlen(s + i);
			continue ;
		}
		i++;
	}
	return (res);
}

char			**ft_split_whitespaces(const char *s)
{
	char		**res;
	size_t		words;

	if (!s)
		return (NULL);
	words = count_words(s);
	if (!(res = (char **)ft_memalloc(sizeof(char *) * (words + 1))))
		return (NULL);
	return (alloc_and_fill(s, res));
}
