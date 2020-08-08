/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:33:32 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/08 17:51:45 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		handle_interrupt(void)
{
	ft_printf("\n$> ");
	g_is_prompt = 0;
}

char		*append_path(char *path, char *arg)
{
	char *prefix;

	if (!(prefix = ft_strjoin(path, "/")))
		malloc_error();
	if (!(prefix = ft_strjoin_free(prefix, arg)))
		malloc_error();
	return (prefix);
}

void		delete_table(char ***table)
{
	int i;

	i = 0;
	if (NULL == table || NULL == *table)
		return ;
	while ((*table)[i])
	{
		free((*table)[i]);
		(*table)[i] = NULL;
		i++;
	}
	free(*table);
	*table = NULL;
}

int			check_file_to_exec(char *path)
{
	struct stat statbuf;

	if (access(path, F_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO,
		"minishell: no such file or directory: %s\n", path);
		g_is_prompt = 1;
		return (-1);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", path);
		g_is_prompt = 1;
		return (-1);
	}
	lstat(path, &statbuf);
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: is a directory\n", path);
		g_is_prompt = 1;
		return (-1);
	}
	return (0);
}

int			execute(char *path, char **av, char **env)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (check_file_to_exec(path) == -1)
		return (-1);
	if ((pid = fork()) == 0)
	{
		if (execve(path, av, env) == -1)
			ft_printf_fd(STDERR_FILENO,
			"minishell: %s: exec format error\n", path);
	}
	else if (pid < 0)
		ft_printf_fd(STDERR_FILENO,
		"minishell: fork: failed to fork a process");
	else
	{
		g_is_prompt = 1;
		wait(0);
	}
	return (1);
}
