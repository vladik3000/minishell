/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:04:19 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/10 19:29:03 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static size_t			ft_strlen_lb(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int				ft_return_line(char **line, char **arr, size_t end)
{
	char *tmp;

	if (end)
	{
		if (!(*line = ft_strsub(*arr, 0, ft_strlen(*arr))))
			return (-1);
		*arr[0] = 0;
		return (1);
	}
	if (!(*line = ft_strsub(*arr, 0, ft_strlen_lb(*arr))))
		return (-1);
	if (!(tmp = ft_strdup(*arr + ft_strlen_lb(*arr) + 1)))
		return (-1);
	ft_strdel(arr);
	*arr = tmp;
	return (1);
}

int						get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*arr[10240];
	char		buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || fd > 10239 || BUFF_SIZE < 1)
		return (-1);
	if ((!arr[fd] && !(arr[fd] = ft_strnew(BUFF_SIZE))))
		return (-1);
	if (ft_strchr(arr[fd], '\n'))
		return (ft_return_line(line, &arr[fd], 0));
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = 0;
		arr[fd] = ft_strjoin_free(arr[fd], buff);
		if (ft_strchr(arr[fd], '\n'))
			return (ft_return_line(line, &arr[fd], 0));
		if (ret < BUFF_SIZE)
			return (ft_return_line(line, &arr[fd], 1));
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && arr[fd][0] != 0)
		return (ft_return_line(line, &arr[fd], 1));
	ft_strdel(&arr[fd]);
	return (0);
}
