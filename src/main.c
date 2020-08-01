/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:15:05 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/16 18:41:54 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int is_prompt;


void	handle_interrupt(int pid)
{
	ft_printf("\n$> ");
	is_prompt = 0;
}

int	check_file_to_exec(char *path)
{
	struct stat statbuf;

	if (access(path, F_OK)== -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: no such file or directory: %s\n", path);
		is_prompt = 1;
		return (-1);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", path);
		is_prompt = 1;
		return (-1);
	}
	lstat(path, &statbuf);
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: is a directory\n", path);
		is_prompt = 1;
		return (-1);
	}
	return (0);
}

int	execute(char *path, char **av, char **env)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (check_file_to_exec(path) == -1)
		return (-1);
	if ((pid = fork()) == 0)
	{
		if (execve(path, av, env) == -1)
			ft_printf_fd(STDERR_FILENO, "minishell: %s: exec format error\n", path);
	}
	else if (pid < 0)
		ft_printf_fd(STDERR_FILENO, "minishell: fork: failed to fork a process");
	else
	{
		is_prompt = 1;
		wait(0);
	}
	return (1);
}

void	search(char **arg, char **env, t_hash_table *ht)
{
	char *cmd;
	
	if (!ft_strchr(arg[0], '/'))
	{
		if (!(cmd = ht_search(ht, arg[0])))
			{
				ft_printf_fd(STDERR_FILENO, "minishell: command not found: %s\n", arg[0]);
				return ;
			}
	}
	else
	{
		cmd = arg[0];
	}

	execute(cmd, arg, env);
}

void	exec_command(char **args, char **env, t_hash_table *ht)
{
	search(args, env, ht);
	
}

int		is_ascii_word(const char *word)
{
	int i = 0;
	while (word[i])
	{
		if ((int)word[i] >= 127 || (int)word[i] <= 0)
			return (0);
		i++;
	}
	return (1);
}


void	handle_input(char *input, char ***env, t_hash_table **ht)
{
	int i;
	int flag;
	char **args;

	flag = 0;
	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			flag = 1;
		i++;
	}
	if (flag)
	{
		if (input && *input)
			if (!(args = ft_strtok(input, &ft_isspace)))
				malloc_error();
		if (is_ascii_word(args[0]) == 0)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", args[0]);
			return;
		}
//		while (args[i] != 0)
//		{
//			ft_printf("%s\n", args[i]);
//			i++;
//		}
		replace_envs(&args, *env);
		if (args[0] != 0)
		{
			if (check_builtin(args, env, ht))
			{	
				delete_table(&args);
				return ;
			}
			else
			{
				exec_command(args, *env, *ht);
			}
			delete_table(&args);
		}
		if (args)
			delete_table(&args);
	}
}

void	minishell(char ***ev, t_hash_table **ht)
{
	char	*line;

	while (42)
	{
		if (is_prompt)
			ft_printf("$> ");
		is_prompt = 1;
		if (get_next_line(STDIN_FILENO, &line) == -1)
			malloc_error();
		if (!line)
			continue ;
		handle_input(line, ev, ht);
		ft_strdel(&line);
	}
	get_next_line(FREE_GNL, NULL);
	delete_table(ev);
}

int main(int ac, char **av, char **environ)
{
	char **ev;
	t_hash_table *ht;
	is_prompt = 1;

	ht = NULL;
	ht = ht_new_sized(10);
    //signal(SIGINT, handle_interrupt);
	if (init_binaries(&ht, environ) == PATH_NOTFOUND)
		ht_delete_hash_table(ht);
	init_ev(&ev, environ);
	minishell(&ev, &ht);
	return (0);
}
