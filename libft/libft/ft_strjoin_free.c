/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:49:09 by fmallist          #+#    #+#             */
/*   Updated: 2020/01/15 17:34:45 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_free(char *s1, char *s2)
{
	char *s;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!(s = ft_strjoin(s1, s2)))
		return (NULL);
	ft_strdel(&s1);
	return (s);
}
