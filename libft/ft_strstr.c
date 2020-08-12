/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:38:33 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/08 20:16:26 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;

	i = 0;
	if (haystack[0] == '\0' && needle[0] == '\0')
		return ((char *)haystack);
	if (*haystack == '\0' || !haystack)
		return (NULL);
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			++j;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
