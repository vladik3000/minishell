/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:38:43 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/26 20:46:02 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long		ft_pow(long long n, size_t power)
{
	size_t		i;
	long long	tmp;

	if (power == 0)
		return (1);
	i = 0;
	tmp = n;
	while (i < power - 1)
	{
		n = n * tmp;
		i++;
	}
	return (n);
}
