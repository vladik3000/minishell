/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:49:22 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/06 19:49:24 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					print_env_table(const char **env)
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

void				copy_table(char ***neww, char **old)
{
	int i;

	i = 0;
	while (old[i])
		i++;
	if (!(*neww = ft_memalloc(sizeof(char *) * (i + 1))))
		malloc_error();
	i = 0;
	while (old[i])
	{
		if (!((*neww)[i] = ft_strdup(old[i])))
			malloc_error();
		i++;
	}
	(*neww)[i] = NULL;
}

int					is_not_equal(int c)
{
	return (c != '=');
}

char				*strip_env_var(char *var)
{
	char *result;

	result = NULL;
	result = ft_strsub(var, 0, ft_strlen_fp(var, is_not_equal));
	if (NULL == result)
		malloc_error();
	return (result);
}

void				append_to_table_help(char ***env, char *var,
					char ***new_env, int i)
{
	char	*stripped_var;
	char	*value;
	int		index;

	stripped_var = strip_env_var(var);
	index = find_env(*env, stripped_var);
	ft_strdel(&stripped_var);
	if (-1 != index)
	{
		value = ft_strsub(var, ft_strlen_fp(var, is_not_equal) + 1,
		ft_strlen(var + ft_strlen_fp(var, is_not_equal)));
		replace_env(new_env, value, index);
		ft_strdel(&value);
	}
	else
	{
		if (!((*new_env)[i] = ft_strdup(var)))
			malloc_error();
	}
}
