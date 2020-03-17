/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:18:21 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/15 16:16:40 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_env(char **ev, char *name)
{
	int i;
	int j;
	size_t namelen;

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

int		is_not_dollar(int c)
{
	return (c != '$');
}

int		is_env(int c)
{
	return (ft_isalnum(c) || c == '_');
}
//TODO norme this 
void	parse_envvar(char ***args, char **env, int index, char *dollar)
{
	size_t len_until_dollar;
	size_t len_after_env;
	size_t len_env;
	int		i;
	char *new_arg;
	char *envname;

	i = 0;
	new_arg = NULL;
	len_until_dollar = ft_strlen_fp((*args)[index], &is_not_dollar);
	if (len_until_dollar)
		if (!(new_arg = ft_strsub((*args)[index], 0, len_until_dollar)))
			malloc_error();
	len_env = ft_strlen_fp(dollar + 1, &is_env);
	envname = ft_strsub((*args)[index], len_until_dollar + 1, len_env);
	len_after_env = ft_strlen(dollar + 1 + len_env);
	if (!envname)
		malloc_error();
	if ((i = find_env(env, envname)) == -1)
	{
		ft_strdel(&envname);
		if (!(new_arg = ft_strjoin_free(new_arg, ((len_env > 0)
		? ((*args)[index] + len_until_dollar + len_env + 1) : NULL))))
			malloc_error();
		free((*args)[index]);
		(*args)[index] = new_arg;
		return ;
	}
	ft_strdel(&envname);
	envname = ft_strdup(env[i] + len_env + 1);
	new_arg = ft_strjoin_free(new_arg, envname);
	if (!envname || !new_arg)
		malloc_error();
	if (!(new_arg = ft_strjoin_free(new_arg, ((len_after_env > 0)
	? ((*args)[index] + len_until_dollar + len_env + 1) : NULL))))
		malloc_error();
	free((*args)[index]);
	ft_strdel(&envname);
	(*args)[index] = new_arg;
}

void	replace_envs(char ***args, char **env)
{
	int index;
	int i;

	i = 0;
	char *dollar;

	dollar = NULL;
	while ((*args)[i])
	{
		if (ft_strequ((*args)[i], "~"))
		{
			if ((index = find_env(env, "HOME")) != -1)
			{
				free((*args)[i]);
				if (!((*args)[i] = ft_strdup(env[index] + 5)))
					malloc_error();
				i++;
				continue ;
			}
		}
		if ((dollar = ft_strchr((*args)[i], '$')))
		{
			if (*(dollar + 1) && ft_isalnum(*(dollar + 1)))
				parse_envvar(args, env, i, dollar);
		}
		i++;
	}
}

void	init_ev(char ***my_table, char **env)
{
	int i;
	int j;
	char **split;
	char *tmp;
	
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