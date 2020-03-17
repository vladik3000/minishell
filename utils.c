/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:33:32 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/01 18:08:34 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_path(char *path, char *arg)
{
	char *prefix;

	if (!(prefix = ft_strjoin(path, "/")))
		malloc_error();
	if (!(prefix = ft_strjoin_free(prefix, arg)))
		malloc_error();
	return (prefix);
	
}

void	delete_table(char ***table)
{
	int i;

	i = 0;
	while ((*table)[i])
	{
		free((*table)[i]);
		(*table)[i] = NULL;
		i++;
	}
	free(*table);
	*table = NULL;
}
