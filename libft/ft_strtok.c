/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:08:16 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/17 17:28:22 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_count_words(char const *s, int (*f)(int))
{
	size_t words;

	words = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (!f(((int)*s)) && (f(((int)(*(s + 1)))) || *(s + 1) == 0))
			words++;
		s++;
	}
	return (words);
}

static size_t		ft_wordlen(char const *s, int (*f)(int))
{
	size_t		i;

	i = 0;
	while (!(f(s[i])) && s[i])
		i++;
	return (i);
}

static void			ft_delete(char ***res, size_t j)
{
	while (--j > 0)
		ft_strdel(&(*res)[j]);
	free(*res);
	*res = NULL;
}

static char			**ft_alloc_and_fill(char const *s,
					int (*f)(int), char **res)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!f(s[i]))
		{
			if (!(res[j] = ft_strsub(s, i, ft_wordlen(s + i, f))))
			{
				ft_delete(&res, j);
				return (NULL);
			}
			j++;
			i += ft_wordlen(s + i, f);
			continue ;
		}
		i++;
	}
	res[j] = NULL;
	return (res);
}

char				**ft_strtok(char const *s, int (*f)(int))
{
	char		**res;
	size_t		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, f);
	if ((res = (char **)malloc(sizeof(char *) * (words + 1))) == NULL)
		return (NULL);
	return (ft_alloc_and_fill(s, f, res));
}
