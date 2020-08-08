/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:07:27 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/08 17:35:05 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			is_ascii_word(const char *word)
{
	int i;

	i = 0;
	while (word[i])
	{
		if ((int)word[i] >= 127 || (int)word[i] <= 0)
			return (0);
		i++;
	}
	return (1);
}

void		init_ev(char ***my_table, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[j])
		j++;
	if (!(*my_table = (char **)ft_memalloc(sizeof(char *) * (j + 1))))
		malloc_error();
	while (*env)
	{
		if (!((*my_table)[i] = ft_strdup(*env)))
			malloc_error();
		i++;
		env++;
	}
	(*my_table)[i] = NULL;
}

int			find_env(char **ev, char *name)
{
	int		i;
	size_t	namelen;

	if (NULL == ev)
		return (-1);
	i = 0;
	namelen = ft_strlen(name);
	while (ev[i])
	{
		if (ft_strnstr(ev[i], name, namelen) != NULL)
		{
			if (ev[i][namelen] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

int			is_not_dollar(int c)
{
	return (c != '$');
}

int			is_env(int c)
{
	return (ft_isalnum(c) || c == '_');
}
