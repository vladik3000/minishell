/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:21:43 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/01 17:05:15 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		malloc_error()
{
	ft_printf_fd(STDERR_FILENO, "minishell: malloc: failed to allocate memory");
	exit(ENOMEM);
}