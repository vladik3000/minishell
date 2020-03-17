/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_fp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:54:56 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/10 21:04:08 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen_fp(char *str, int (*f)(int))
{
	size_t len;
	size_t i;

	i = 0;
	len = 0;
	while (str[i] && f(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}
