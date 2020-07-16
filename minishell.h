/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:16:57 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/15 16:19:48 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/ft_printf/ft_printf.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/param.h>
# include <sys/dir.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>

# define PATH_NOTFOUND -4
# define N 1
# define E 2
# define HT_PRIME_1 151
# define HT_PRIME_2 163
# define HT_INIT_BASE_SIZE 100

typedef struct	s_ht_item
{
	char *key;
	char *value;
}				t_ht_item;



extern t_ht_item	g_ht_deleted_item;

typedef struct	s_hash_table
{
	size_t		size_index;
	size_t 		size;
	size_t		count;
	t_ht_item	**items;
}				t_hash_table;



//void	builtin_cd(char **args, char **env);
int	execute(char *path, char **av, char **env);
void	init_ev(char ***my_table, char **env);
int		builtin_cd(char **args, char **env);
int		builtin_setenv(char **args, char ***env, t_hash_table **ht);
int		builtin_unsetenv(char **args, char ***env, t_hash_table **ht);
int		builtin_env(char **args, char **env, t_hash_table **ht);
int		check_builtin(char **args, char ***env, t_hash_table **ht);
int		builtin_echo(char **args, char **env);
void	builtin_exit(char **args, char ***env, t_hash_table **ht);
void	error_msg(char *error, char *msg);
void	builtin_exit();
void	error(char *msg);
int		find_env(char **ev, char *name);
char	*append_path(char *path, char *arg);
int		init_binaries(t_hash_table **ht, char **ev);
void	malloc_error();
void	delete_table(char ***table);
void	replace_envs(char ***args, char **env);
t_hash_table		*ht_new_sized(const size_t size_index);
void				ht_delete_hash_table(t_hash_table *ht);
void				ht_delete_item(t_ht_item *item);
void				ht_delete_from_table(t_hash_table *ht, const char *key);
t_ht_item			*ht_new_item(const char *k, const char *v);
int					ht_insert(t_hash_table *ht, const char *k, const char *v);
char				*ht_search(t_hash_table *ht, const char *k);
int					ht_resize(t_hash_table *ht, const int dir);



#endif
