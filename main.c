/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:15:05 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/12 22:06:25 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/ft_printf.h"
#include <limits.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <errno.h>

void error(char *msg)
{
	write(2, "minishell:", ft_strlen("minishell:"));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(-1);
}

void	delete_table(char **table)
{
	int i;

	i = 0;
	while (table[i])
	{
		ft_memdel((void *)&table[i]);
		i++;
	}
	free(table);
	table = NULL;
}

int		find_path(char **envp)
{
	int i;

	i = 0;
	while (envp[i] && *envp[i])
	{
		if (*envp[i] == 'P' && *(envp[i] + 1) == 'A'
		&& *(envp[i] + 2) == 'T' && *(envp[i] + 3) == 'H')
			break ;
		i++;
	}
	return (i);
}

char	*append_path(char *path, char *arg)
{
	char *prefix;

	if (ft_strchr(arg, '/'))
		return (arg);
	if (!(prefix = ft_strjoin(path, "/")))
		error("malloc: failed to allocate memory");
	if (!(prefix = ft_strjoin_free(prefix, arg)))
		error("malloc: failed to allocate memory");
	return (prefix);
	
}

int	execute(char *path, char **av, char **envp)
{
	pid_t pid;
	int i = 0;
	//ft_printf("path[%s]\n", path);
	if (access(path, F_OK) == -1)
	{
		//ft_printf("no\n");
		return (-1);
	}
	ft_printf("path:[%s]\n", path);
	while (av[i])
	{
		ft_printf("av[%d]: {%s}\n", i, av[i]);
		i++;
	}
	i = 0;
	while (envp[i])
	{
		ft_printf("env[%d]: {%s}\n", i, envp[i]);
		i++;
	}
	if ((pid = fork()) == 0)
	{
		if (execve(path, av, envp) == -1)
			ft_printf("errno:%d NOOOO\n", errno);
	}
	else if (pid < 0)
		ft_printf("fork fail");
	else
	{
		wait(0);
	}
	
	return (1);
}

void	search(char **paths, char **arg, char **env)
{
	int j;
	int found;
	char *path;

	j = 0;
	found = 0;
	while (found != 1)
	{
		path = append_path(paths[j], *arg);
		if (execute(path, arg, env) != -1)
		{
			found = 1;
			//ft_memdel((void *)&path);
		}
		j++;
	}
}

void	search_for_command(char **args, char **envp)
{
	int		found;
	int		i;
	int		j;
	char	**to_search;

	found = 1;
	j = 0;
	i = find_path(envp);
	if (!(to_search = ft_strsplit(envp[i] + 5, ':')))
		error("malloc: failed to allocate memory");
	//while (found)
	//{
	search(to_search, args, envp);
	//delete_table(to_search);
	//}
}


void	exec_command(char **args, char **envp)
{
	search_for_command(args, envp);
	
}

void handle_input(char *input, char **envp)
{
	int i;
	int flag;
	char **args;

	flag = 0;
	i = 0;
	ft_printf("input:[%s]\n", input);
	while (input[i++])
	{
		if (!ft_isspace(input[i]))
			flag = 1;
		i++;
	}
	if (flag)
	{
		if (input && *input)
			if (!(args = ft_split_whitespaces(input)))
				error("malloc: failed to allocate memory");
		if (args[0] != 0)
			exec_command(args, envp);
		delete_table(args);
	}
}

void	init_ev(char ***my_table, char **envp)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (envp[j])
		j++;
	if (!(*my_table = (char **)ft_memalloc(sizeof(char *) * (j + 1))))
		error("malloc: failed to allocate memory");
 	while (*envp)
 	{
 		if (!((*my_table)[i] = ft_strdup(*envp)))
		 	error("malloc: failed to allocate memory");
 		i++;
 		envp++;
 	}
	 (*my_table)[i] = NULL;
}


void	minishell(char **ev)
{
	char	*line;
	int		status;

	status = 1;
	while (status)
	{
		ft_printf("$> ");
		get_next_line(0, &line);
		handle_input(line, ev);
		//ft_printf("uhm\n");
		//delete_table(ev);
		ft_strdel(&line);
	}
	delete_table(ev);
}

int main(int ac, char **av, char **envp)
{
	char **ev;
	
	init_ev(&ev, envp);
	minishell(ev);
	return (0);
}
