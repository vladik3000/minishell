/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:16:33 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/19 16:21:19 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	cderror()
// {
// 	write(2, "cd: error\n", ft_strlen("cd: error\n"));
// }

// static void	noexist(char *path)
// {
// 	write(2, "cd: no such file or directory: ", ft_strlen("cd: no such file or directory: "));
// 	write(2, path, ft_strlen(path));
// 	write(2, "\n", 1);
// }

// void		builtin_cd(char **args, char **env)
// {
// 	char cwd[PATH_MAX];

// 	if (access(, F_OK) == -1)
// 		noexist(path);
// 	getcwd(cwd, PATH_MAX);
// 	ft_strcat(cwd, "/");
// 	ft_strcat(cwd, path);
// 	if (chdir(cwd) == -1)
// 		cd_error();
// }
