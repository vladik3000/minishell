/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:19:38 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/11 20:13:11 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*res;

	i = 0;
	if ((len + 1 < len) || !s || !len || start >= ft_strlen(s))
		return (NULL);
	if ((res = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
