/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:51:05 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/06 19:51:29 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				is_bad_usage(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	if (i != 3 || !((ft_strequ(args[2], "0") || ft_strequ(args[2], "1")))
	|| (ft_strchr(args[1], '=') == NULL))
	{
		ft_printf_fd(STDERR_FILENO,
		"setenv: usage:\nsetenv [name=value] [override: (0 or 1)]\n");
		return (-1);
	}
	if (ft_strequ(args[2], "0"))
		return (0);
	else
		return (1);
	return (0);
}

int				replace_env(char ***env, char *value, int index)
{
	char	*new_var;
	int		equal;
	char	*tmp;

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

void			append_ev(char ***my_table, char **env, char *neww)
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
	(*my_table)[i] = neww;
	(*my_table)[i + 1] = NULL;
}
