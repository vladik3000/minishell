/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:34:16 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/23 17:26:12 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	print_home(char **env)
{
	int i;
	char *equal_sign;
	
	i = 0;
	while (env[i])
	{
		if (ft_strlen(env[i]) < 5)
		{
			i++;
			continue ;
		}
		equal_sign = ft_strchr(env[i], '=');
		if (!equal_sign)
		{
			i++;
			continue ;
		}
		if (*env[i] == 'H' && *(env[i] + 1) == 'O' && *(env[i] + 2) == 'M'
		&& *(env[i] + 3) == 'E' && (equal_sign - env[i]) == 4)
		{
			ft_putstr(equal_sign + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	search_env(char *arg, char **env)
{
	size_t len;
	char *tmp;
	int i;

	i = 0;
	len = ft_strlen(arg);
	if (len == 0)
	{
		ft_putchar('$');
		return (1);
	}
	else
	{
		while (env[i])
		{
			tmp = ft_strchr(env[i], '=');
			if ((tmp - env[i]) != len)
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
	}
	return (0);
}

static void		echo_print_arg(char *arg, char **env)
{
	int i;

	i = 0;
	if (arg[0] == '$')
	{
		search_env(arg + 1, env);
		return ;
	}
	if (arg[0] == '~' && ft_strlen(arg) == 1)
	{
		if (print_home(env) == 1)
			return ;
	}
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
			if (arg[i] == 'n')
				ft_putchar('\n');
			else if (arg[i] == 'b')
				ft_putchar('\b');
			else if (arg[i] == 't')
				ft_putchar('\t');
			else if (arg[i] == 'v')
				ft_putchar('\v');
			else if (arg[i] == 'a')
				ft_putchar('\a');
			else if (arg[i] == 0)
			{
				ft_putchar('\\');
				break;
			}
			else
				ft_putchar('\\');
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

static int		parse_flags(char **args)
{

	if (ft_strlen(args[1]) == 2 && args[1][0] == '-' && args[1][1] == 'n')
		return (2);
	return (1);
}
int		builtin_echo(char **args, char **env)
{
	int flag;
	int i;

	flag = 0;
	i = 1;
	if (args[1])
		i = parse_flags(args);
	if (i == 2)
		flag = 1;
	if (!args[i] && i != 2)
	 	ft_putchar('\n');
	else
	{
		while (args[i])
		{
			echo_print_arg(args[i], env);
			if (args[i + 1])
				ft_putchar(' ');
			i++;
		}
		if (!flag)
			ft_putchar('\n');
	}
	return (1);
}