/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:33:43 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/11 17:52:26 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	size_t			size;
	size_t			i;

	i = 0;
	if (NULL == s1 || NULL == s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if ((res = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (*s1 != '\0')
		res[i++] = *s1++;
	while (*s2 != '\0')
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}
