/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 09:09:25 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/11 20:15:28 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				set_oldpwd(char ***env, char *oldpwd)
{
	int		i;
	char	*tmp;

	i = 0;
	if ((i = find_env(*env, "OLDPWD")) == -1)
		return ;
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	ft_strdel(&((*env)[i]));
	(*env)[i] = tmp;
}

int					check_tilda(char *tilda, char *arg)
{
	if (ft_strlen(arg) == 1)
		return (1);
	if (!ft_strequ(tilda, arg))
		return (-1);
	if (*(tilda + 1) != '/')
		return (-1);
	return (1);
}

int					replace_home(char **arg, char **env, char *tilda)
{
	char		*tmp;
	int			index;

	index = -1;
	tmp = NULL;
	if (check_tilda(tilda, *arg) == -1)
		return (1);
	if ((index = find_env(env, "HOME")) != -1)
	{
		if (ft_strlen(*arg) == 1)
		{
			ft_strdel(arg);
			if (!((*arg) = ft_strdup(env[index] + 5)))
				malloc_error();
		}
		else
		{
			if (!(tmp = ft_strjoin(env[index] + 5, tilda + 1)))
				malloc_error();
			ft_strdel(arg);
			*arg = tmp;
		}
		return (1);
	}
	return (0);
}

void				recreate_ht(char **env, t_hash_table **ht)
{
	int i;

	i = -1;
	if ((i = find_env(env, "PATH")) != -1)
	{
		if (ft_strnequ(env[i], "PATH", 4))
		{
			if (*ht != NULL)
				ht_delete_hash_table(*ht);
			*ht = NULL;
			*ht = ht_new_sized(10);
			init_binaries(ht, env);
		}
	}
}
