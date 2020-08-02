/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:48:37 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/16 21:12:45 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_env_table(const char **env)
{
	int i;

	i = 0;
    if (!env)
        return (-1);
    while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (1);
}

void		copy_table(char ***new, char **old)
{
	int i;

	i = 0;
	while (old[i])
		i++;
	if (!(*new = ft_memalloc(sizeof(char *) * (i + 1))))
		malloc_error();
	i = 0;
	while (old[i])
	{
		if (!((*new)[i] = ft_strdup(old[i])))
			malloc_error();
		i++;
	}
	(*new)[i] = NULL;
}

void		append_to_table(char ***env, char *var)
{
	int i;
	char **new_env;
	int index;

	index = 0;
	new_env = NULL;
	i = 0;
	while (*env && (*env)[i])
		i++;
	if (!(new_env = ft_memalloc(sizeof(char *) * (i + 2))))
		malloc_error();
	i = 0;
	while (*env && (*env)[i])
	{
	    if (!(new_env[i] = ft_strdup((*env)[i])))
		    malloc_error();
		i++;
    }
	index = find_env(*env, var);
	if (-1 != index)
	{
		ft_printf("FOUND!!!!");
		replace_env(env, var, index);
	}
	else
	{
		if (!(new_env[i] = ft_strdup(var)))
			malloc_error();
	}
	new_env[i + 1] = NULL;
    if (env && *env)
	    delete_table(env);
	*env = new_env;
}

static char **build_envs(char **args, char **env, int is_ignore)
{
	int i;
	char **local_env;
	char *equal_sign;

	equal_sign = NULL;
	i = 1;
	local_env = NULL;
	if (!is_ignore)
		copy_table(&local_env, env);
    else
        i = 2;
	while (args[i])
	{
		if (!(equal_sign = ft_strchr(args[i], '=')))
			break;
		if (ft_strlen(args[i]) < 3)
			break;
		if (!(*(equal_sign + 1)) || !(*(equal_sign - 1)))
			break;
		append_to_table(&local_env, args[i]); // NEED TO CALL SETENV
		i++;
	}
	return (local_env);
}

int		find_exec(char **args)
{
	int i;
	char *equal;

	equal = NULL;
	i = 0;
    while (args[i])
	{
		if (ft_strequ(args[i], "-i") || 0 == i)
		{
			i++;
			continue ;
		}
		if (!(equal = ft_strchr(args[i], '=')))
		{
		//	ft_printf("i[%d][%s]\n", i, args[i]);
			return (i);
		}
		i++;
	}

    return (0);
}

int		execute_arg(char *arg, char **args, char **local_env, t_hash_table *ht)
{
	char *new_arg;

	new_arg = NULL;
	if (ft_strchr(arg, '/'))
		new_arg = arg;
	else
		new_arg = ht_search(ht, arg);
	if (execute(new_arg, args, local_env) == -1)
	{
		delete_table(&local_env);
		return (-1);
	}
	return (1);
}

int		builtin_env(char **args, char **env, t_hash_table **ht)
{
	char	**local_env;
	int		is_ignore;
	int		exec;


	is_ignore = 0;
	local_env = NULL;
	if (ft_strequ(args[1], "-i"))
		is_ignore = 1;
	local_env = build_envs(args, env, is_ignore);
	int	i = 0;
	//	while (args[i] != 0)
	//	{
	//		ft_printf("BBB%s$\n", args[i]);
	//		i++;
	//	}
	//int i = 0;
	//while (args[i])
//	{
//		ft_printf("args:[%s]\n", args[i]);
//		i++;
//	}
	if (!(exec = find_exec(args)))
	{
		print_env_table((const char **)local_env);
		delete_table(&local_env);
		return (1);
	}
	return (execute_arg(args[exec], args + exec, local_env, *ht));
}
