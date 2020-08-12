/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:27:19 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/11 20:08:08 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		*create_new_var(char *name, char *value)
{
	char *new_var;

	new_var = NULL;
	if (!(new_var = ft_memalloc(sizeof(char) * (ft_strlen(name)
	+ ft_strlen(value) + 2))))
		malloc_error();
	ft_strcpy(new_var, name);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	return (new_var);
}

void			override_env(char ***env, char *value, t_hash_table **ht, int i)
{
	replace_env(env, value, i);
	recreate_ht(*env, ht);
}

static void		help(char *name, char *value, char ***env, char ***new_env)
{
	char *new_var;
	char **tmp;

	new_var = create_new_var(name, value);
	append_ev(new_env, *env, new_var);
	tmp = *env;
	*env = *new_env;
	delete_table(&tmp);
}

void			delete_twostr(char **a, char **b)
{
	ft_strdel(a);
	ft_strdel(b);
}

int				builtin_setenv(char **args, char ***env, t_hash_table **ht)
{
	int		i;
	int		override;
	char	**new_env;
	char	*value;
	char	*name;

	new_env = NULL;
	if ((override = is_bad_usage(args)) == -1)
		return (-1);
	name = strip_env_var(args[1]);
	value = ft_strsub(args[1], ft_strlen_fp(args[1], is_not_equal) + 1,
			ft_strlen(args[1] + ft_strlen_fp(args[1], is_not_equal)));
	if (((i = find_env(*env, name)) != -1) && override)
		override_env(env, value, ht, i);
	else
	{
		help(name, value, env, &new_env);
		recreate_ht(*env, ht);
	}
	delete_twostr(&name, &value);
	return (1);
}
