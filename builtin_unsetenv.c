/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:47:55 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/07 17:22:37 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int env_var_not_found(char *name)
{
	ft_printf_fd(STDERR_FILENO, "unsetenv: %s: environmental variable not found, nothing to unset", name);
	return (-1);
}

static int usage()
{
	ft_printf_fd(STDERR_FILENO, "unsetenv:\nusage: unsetenv [NAME]");
	return (-1);
}

static int unset(char ***env, int index)
{
	int		i;
	int		j;
	char **new_env;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	if (!(new_env = ft_memalloc(sizeof(char *) * i)))
		malloc_error();
	i = 0;
	while ((*env)[i])
	{
		if (i == index)
		{
			i++;
			continue ;
		}
		if (!(new_env[j] = ft_strdup((*env)[i])))
			malloc_error();
		i++;
		j++;
	}
	new_env[j] = NULL;
	delete_table(env);
	*env = new_env;
	return (1);
}

int		builtin_unsetenv(char **args, char ***env, t_hash_table **ht)
{
	int i;

	i = 0;
	if (!args[1])
		return (usage());
	if ((i = find_env(*env, args[1])) == -1)
		return (env_var_not_found(args[1]));
	if (ft_strequ(args[1], "PATH"))
	{
		ht_delete_hash_table(*ht);
		*ht = NULL;
	}
	unset(env, i);
	return (1);
}