/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:49:24 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/15 16:21:20 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_exit(char **args, char ***env, t_hash_table **ht)
{
	if (args != NULL)
		delete_table(&args);
	if (env != NULL && *env != NULL)
		delete_table(env);
	if (*ht != NULL && ht != NULL)
		ht_delete_hash_table(*ht);
	exit(0);
}