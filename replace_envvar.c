/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envvar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:24:29 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/26 19:07:59 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		parse_arg(char *arg)
{
	char *dollar;
	

	if (!(dollar = ft_strchr(arg, '$')) || )
		return (-1);
}

static size_t envlen(char *arg)
{

}
char	*parse_dollar(char *arg, char *dollar)
{
	size_t		start;
	size_t		end;
	size_t		len;
	char		*res;
	
	start = 0;
	end = 0;
	len = 0;
	res = NULL;
	while (arg[start] && arg[start] != '$')
		start++;
	start++;
	end = start;
	while (arg[end] && (ft_isalnum(arg[end]) || arg[end] == '_'))
	{
		len++;
		end++;
	}
	if (len)
	{
		
	}
}

void	replace_envs(char **args, char **env)
{
	int i;
	int j;
	char *dollar;
	char *envvar;
	
	i = 0;
	while (args[i])
	{
		parse_arg(args[i]);
		if (!(dollar = ft_strchr(args[i], '$')))
		{
			i++;
			continue ;
		}
		else if (!(*(dollar + 1)))
		{
			i++;
			continue ;
		}
		while (args[i][j] != '$')
			j++;
		if (args[i][j + 1])
			j++;
		
		parse_dollar(args[i]);
		i++;
	}
}
