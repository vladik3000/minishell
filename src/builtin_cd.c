/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:42:39 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/15 17:43:06 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int if_bad_usage(char **args)
{
	if (args[1] && args[2])
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static int	check_file_to_cd(char *path)
{
	struct stat statbuf;

	if (access(path, X_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: no such file or directory\n", path);
		return (-1);
	}
	lstat(path, &statbuf);
	if ((statbuf.st_mode & S_IFMT) != S_IFDIR)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: is not a directory\n", path);
		return (-1);
	}
	return (0);
}


static int cd_prev(char **env)
{
	int i;
	char *prev;

	prev = NULL;
	if ((i = find_env(env, "OLDPWD")) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: -: no such file or directory");
		return (-1);
	}
	prev = env[i] + 7;
	if (check_file_to_cd(prev) == -1)
		return (-1);
	if (prev)
	{
		if (chdir(prev) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "cd: %s: failed to open", prev);
			return (-1);
		}
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "cd: -: no such file or directory");
		return (-1);
	}
	return (1);
}

static int cd_home(char **env)
{
	int		i;
	char	*home;

	home = NULL;
	if ((i = find_env(env, "HOME")) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: ~: no such file or directory\n");
		return (-1);
	}
	home = env[i] + 5;
	if (check_file_to_cd(home) == -1)
		return (-1);
	if (home)
	{
		if (chdir(home) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "cd: %s: failed to open\n", home);
			return (-1);
		}
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "cd: ~: no such file or directory\n");
		return (-1);
	}
	return (1);
}

int		builtin_cd(char **args, char **env)
{
	int i;
	char *path;

	int j = 0;
	if (if_bad_usage(args))
		return (1);
	if (!args[1])
		return (cd_home(env));
	if (ft_strequ(args[1], "-"))
		return (cd_prev(env));
	if (check_file_to_cd(args[1]) == -1)
		return (-1);
	if (chdir(args[1]) == -1)
	{
		ft_printf_fd(STDERR_FILENO,
		"cd: chdir: %s: failed to open", args[1]);
		return (-1);
	}
	return (1);
}
