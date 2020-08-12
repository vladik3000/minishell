/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:15:05 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/10 08:35:15 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		search(char **arg, char **env, t_hash_table *ht)
{
	char *cmd;

	if (!ft_strchr(arg[0], '/'))
	{
		if (!(cmd = ht_search(ht, arg[0])))
		{
			ft_printf_fd(STDERR_FILENO,
			"minishell: command not found: %s\n", arg[0]);
			return ;
		}
	}
	else
	{
		cmd = arg[0];
	}
	execute(cmd, arg, env);
}

void		check(char ***args, char ***env, t_hash_table **ht)
{
	replace_envs(args, *env);
	if ((*args)[0] != 0)
	{
		if (check_builtin(*args, env, ht))
		{
			delete_table(args);
			return ;
		}
		else
			search(*args, *env, *ht);
		delete_table(args);
	}
	if (args && *args)
		delete_table(args);
}

void		handle_input(char *input, char ***env, t_hash_table **ht)
{
	int		i;
	int		flag;
	char	**args;

	flag = 0;
	i = -1;
	args = NULL;
	while (input[++i])
	{
		if (!ft_isspace(input[i]))
			flag = 1;
	}
	if (flag)
	{
		if (input && *input)
			if (!(args = ft_strtok(input, &ft_isspace)))
				malloc_error();
		if (is_ascii_word(args[0]) == 0)
		{
			ft_printf_fd(STDERR_FILENO,
			"minishell: %s: command not found\n", args[0]);
			return ;
		}
		check(&args, env, ht);
	}
}

void		minishell(char ***ev, t_hash_table **ht)
{
	char	*line;
	char	*emoji;

	if (!(emoji = ft_strdup("\xF0\x9F\x92\x9E\0")))
		malloc_error();
	line = NULL;
	while (42)
	{
		if (g_is_prompt)
			ft_printf("%s ", emoji);
		g_is_prompt = 1;
		if (get_next_line(STDIN_FILENO, &line) == -1)
			malloc_error();
		if (!line)
			continue ;
		handle_input(line, ev, ht);
		ft_strdel(&line);
	}
	ft_strdel(&emoji);
	get_next_line(FREE_GNL, NULL);
	delete_table(ev);
}

int			main(int ac, char **av, char **environ)
{
	char			**ev;
	t_hash_table	*ht;

	g_is_prompt = 1;
	ht = NULL;
	ht = ht_new_sized(10);
	signal(SIGINT, handle_interrupt);
	if (init_binaries(&ht, environ) == PATH_NOTFOUND)
		ht_delete_hash_table(ht);
	init_ev(&ev, environ);
	minishell(&ev, &ht);
	return (0);
	(void)ac;
	(void)av;
}
