/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:41:02 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/08 17:36:05 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		remove_quotes(char *str)
{
	size_t n;
	size_t j;
	size_t i;

	i = 0;
	j = 0;
	n = ft_strlen(str);
	while (j < n)
	{
		if (str[i] != '"' && str[i] != '\'')
			str[j++] = str[i];
		i++;
	}
	str[j] = 0;
}

int			search_env_loop(char *arg, char **env, size_t len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strchr(env[i], '=');
		if ((tmp - env[i]) != (long)len)
		{
			i++;
			continue ;
		}
		if (ft_strnequ(env[i], arg, len))
		{
			ft_putstr(tmp + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int			print_nonprint(char arg)
{
	if (arg == 'n')
		ft_putchar('\n');
	else if (arg == 'b')
		ft_putchar('\b');
	else if (arg == 't')
		ft_putchar('\t');
	else if (arg == 'v')
		ft_putchar('\v');
	else if (arg == 'a')
		ft_putchar('\a');
	else if (arg == 0)
	{
		ft_putchar('\\');
		return (-1);
	}
	else
		ft_putchar('\\');
	return (1);
}

void		print_loop(char *arg, char **env)
{
	size_t i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (search_env(arg + i + 1, env) == 1)
				return ;
		}
		if (arg[i] == '\\' && (ft_strlen(arg) > i + 1) && arg[i + 1] == '\\')
		{
			i += 2;
			if (print_nonprint(arg[i]) == -1)
				break ;
		}
		else if (arg[i] == '\\' && arg[i + 1] != '\\')
		{
			i++;
			continue ;
		}
		else if (arg[i] != '\\')
			ft_putchar(arg[i]);
		i++;
	}
}
