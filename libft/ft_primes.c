/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_primes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:00:54 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/26 21:28:56 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_prime(const int x)
{
	int i;

	if (x <= 1)
		return (0);
	if (x < 4)
		return (1);
	if ((x % 2) == 0 || (x % 3) == 0)
		return (0);
	i = 3;
	while (i < x / 2)
	{
		if ((x % i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_next_prime(int x)
{
	while (ft_is_prime(x) != 1)
		x++;
	return (x);
}
