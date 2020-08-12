/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:42:39 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/10 09:12:40 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			if_bad_usage(char **args)
{
	if (args[1] && args[2])
	{
		ft_printf_fd(STDERR_FILENO, "cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static int			check_file_to_cd(char *path)
{
	struct stat statbuf;

	if (access(path, X_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO,
		"cd: %s: no such file or directory\n", path);
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

static int			cd_prev(char ***env, char *cwd)
{
	char	*prev;

	if (find_env(*env, "OLDPWD") == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: OLDPWD variable not found");
		return (-1);
	}
	prev = (*env)[find_env(*env, "OLDPWD")] + 7;
	if (check_file_to_cd(prev) == -1)
		return (-1);
	if (prev)
	{
		if (chdir(prev) == -1)
		{
			ft_printf_fd(STDERR_FILENO, "cd: %s: failed to open\n", prev);
			return (-1);
		}
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "cd: -: no such file or directory\n");
		return (-1);
	}
	set_oldpwd(env, cwd);
	return (1);
}

static int			cd_home(char ***env, char *cwd)
{
	char	*home;

	if (find_env(*env, "HOME") == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: ~: no such file or directory\n");
		return (-1);
	}
	home = (*env)[find_env(*env, "HOME")] + 5;
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
	set_oldpwd(env, cwd);
	return (1);
}

int					builtin_cd(char **args, char ***env)
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if (if_bad_usage(args))
		return (1);
	if (!args[1])
		return (cd_home(env, cwd));
	if (ft_strequ(args[1], "-"))
		return (cd_prev(env, cwd));
	if (check_file_to_cd(args[1]) == -1)
		return (-1);
	if (chdir(args[1]) == -1)
	{
		ft_printf_fd(STDERR_FILENO,
		"cd: chdir: %s: failed to open\n", args[1]);
		return (-1);
	}
	set_oldpwd(env, cwd);
	return (1);
}
