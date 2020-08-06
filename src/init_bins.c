/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:01:49 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/06 20:07:04 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		insert(char *path_splitted, struct dirent *entry,
				t_hash_table **ht)
{
	char *bin_path;

	bin_path = NULL;
	if (*(entry->d_name) != '.')
	{
		bin_path = append_path(path_splitted, entry->d_name);
		if (ht_insert(*ht, entry->d_name, bin_path) == -1)
			malloc_error();
		ft_strdel(&bin_path);
	}
}

static int		search_and_insert(char **path_splitted, t_hash_table **ht)
{
	struct dirent	*entry;
	DIR				*d;
	int				i;

	i = 0;
	while (path_splitted[i])
	{
		if ((d = opendir(path_splitted[i])) == NULL)
		{
			i++;
			continue ;
		}
		while ((entry = readdir(d)) != NULL)
			insert(path_splitted[i], entry, ht);
		closedir(d);
		i++;
	}
	return (0);
}

int				init_binaries(t_hash_table **ht, char **ev)
{
	int		i;
	int		path_index;
	char	**path_splitted;
	int		path_notfound;

	i = 0;
	if ((path_index = find_env(ev, "PATH")) == -1)
		return (PATH_NOTFOUND);
	if (!(path_splitted = ft_strsplit(ev[path_index] + 5, ':')))
		malloc_error();
	search_and_insert(path_splitted, ht);
	delete_table(&path_splitted);
	return (0);
}
