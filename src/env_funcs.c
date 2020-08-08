/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:18:21 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/08 17:14:42 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_envvar_help_1(size_t *len_until_dollar,
		char **new_arg, char ***args, int index)
{
	*new_arg = NULL;
	*len_until_dollar = ft_strlen_fp((*args)[index], &is_not_dollar);
	if (len_until_dollar)
		if (!(*new_arg = ft_strsub((*args)[index], 0, *len_until_dollar)))
			malloc_error();
}

void	parse_envvar_help_2(t_envlen l, char **args,
		char **new_arg, char **envname)
{
	ft_strdel(envname);
	if (!(*new_arg = ft_strjoin_free(*new_arg, ((l.len_env > 0)
	? (*args + l.len_until_dollar + l.len_env + 1) : NULL))))
		malloc_error();
	free(*args);
	*args = *new_arg;
	return ;
}

void	parse_envvar_help_3(char **envname,
		char **env, t_envlen l, char **new_arg)
{
	ft_strdel(envname);
	*envname = ft_strdup(env[find_env(env, *envname)] + l.len_env + 1);
	*new_arg = ft_strjoin_free(*new_arg, *envname);
	if (!(*envname) || !(*new_arg))
		malloc_error();
}

void	parse_envvar(char ***args, char **env, int index, char *dollar)
{
	t_envlen	l;
	int			i;
	char		*new_arg;
	char		*envname;

	i = 0;
	parse_envvar_help_1(&l.len_until_dollar, &new_arg, args, index);
	l.len_env = ft_strlen_fp(dollar + 1, &is_env);
	if (!(envname = ft_strsub((*args)[index],
		l.len_until_dollar + 1, l.len_env)))
		malloc_error();
	l.len_after_env = ft_strlen(dollar + 1 + l.len_env);
	if ((i = find_env(env, envname)) == -1)
	{
		parse_envvar_help_2(l, &((*args)[index]), &new_arg, &envname);
		return ;
	}
	parse_envvar_help_3(&envname, env, l, &new_arg);
	if (!(new_arg = ft_strjoin_free(new_arg, ((l.len_after_env > 0)
	? ((*args)[index] + l.len_until_dollar + l.len_env + 1) : NULL))))
		malloc_error();
	free((*args)[index]);
	ft_strdel(&envname);
	(*args)[index] = new_arg;
}

void	replace_envs(char ***args, char **env)
{
	int		index;
	int		i;
	char	*dollar;

	i = 0;
	dollar = NULL;
	index = 0;
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
			if (*(dollar + 1) && ft_isalnum(*(dollar + 1)))
				parse_envvar(args, env, i, dollar);
		i++;
	}
}
