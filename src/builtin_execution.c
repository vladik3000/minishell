/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:38:04 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/15 16:18:17 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_builtin(char **args, char ***env, t_hash_table **ht)
{
		//int i = 0;
		//while (args[i] != 0)
		//{
	//		ft_printf("%s\n", args[i]);
//			i++;
//		}
	if (ft_strequ(*args, "echo"))
		return (builtin_echo(args, *env));
	else if (ft_strequ(*args, "cd"))
		return (builtin_cd(args, *env));
	else if (ft_strequ(*args, "setenv"))
		return (builtin_setenv(args, env, ht));
	else if (ft_strequ(*args, "unsetenv"))
		return (builtin_unsetenv(args, env, ht));
	else if (ft_strequ(*args, "env"))
		return (builtin_env(args, *env, ht));
	else if (ft_strequ(*args, "exit"))
		builtin_exit(args, env, ht);
	return (0);
}
