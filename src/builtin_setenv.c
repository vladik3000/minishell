/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:27:19 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/16 19:27:02 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_bad_usage(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	if (i != 4 && !((ft_strequ(args[3], "0") || ft_strequ(args[3], "1"))))
	{
		ft_printf_fd(STDERR_FILENO,
		"setenv: usage:\nsetenv [name=value] [override: (0 or 1)]\n");
		return (-1);
	}
	if (ft_strequ(args[3], "0"))
		return (0);
	else
		return (1);
	return (0);
}

int replace_env(char ***env, char *value, int index)
{
	char *new_var;
	int equal;
	char *tmp;

	equal = ft_strchr((*env)[index], '=') + 1 - (*env)[index];
	if (!(new_var = ft_memalloc(sizeof(char) * (equal + ft_strlen(value) + 1))))
		malloc_error();
	ft_strncpy(new_var, (*env)[index], equal);
	ft_strncat(new_var, value, ft_strlen(value));
	tmp = (*env)[index];
	(*env)[index] = new_var;
	free(tmp);
	tmp = NULL;
	return (0);
}

static void	append_ev(char ***my_table, char **env, char *new)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (env[j])
		j++;
	if (!(*my_table = (char **)ft_memalloc(sizeof(char *) * (j + 2))))
		malloc_error();
 	while (*env)
 	{
 		if (!((*my_table)[i] = ft_strdup(*env)))
		 	malloc_error();
 		i++;
 		env++;
 	}
	 (*my_table)[i] = new;
	 (*my_table)[i + 1] = NULL;
}

static char	*create_new_var(char *name, char *value)
{
	char *new_var;

	new_var = NULL;
	if (!(new_var = ft_memalloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2))))
		malloc_error();
	ft_strcpy(new_var, name);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	return (new_var);
}

int		builtin_setenv(char **args, char ***env, t_hash_table **ht)
{
	int i;
	int override;
	char **new_env;
	char *new_var;
	
	new_env = NULL;
	new_var = NULL;
	if ((override = is_bad_usage(args)) == -1)
		return (-1);
	if ((i = find_env(*env, args[1])) != -1)
	{
		if (override)
		{
			replace_env(env, args[2], i);
			if (ft_strnequ((*env)[i], "PATH", 4))
				{
					if (*ht != NULL)
						ht_delete_hash_table(*ht);
					*ht = NULL;
					*ht = ht_new_sized(10);//TODO:fix the damn hashtable funcs
					init_binaries(ht, *env);
				}
		}
		else
			return (1);
	}
	else
	{
		new_var = create_new_var(args[1], args[2]);
		append_ev(&new_env, *env, new_var);
		*env = new_env;
		if (ft_strequ(args[1], "PATH"))
		{
			*ht = ht_new_sized(10);
			init_binaries(ht, *env);
		}
		return (1);
	}
	return (1);
}
