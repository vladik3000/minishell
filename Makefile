# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 16:05:25 by fmallist          #+#    #+#              #
#    Updated: 2020/03/10 21:21:33 by fmallist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
LIB=libft/libftprintf.a
SRC=builtin_cd.c		builtin_echo.c	builtin_execution.c \
	builtin_exit.c		env_funcs.c		errors.c			\
	hash_table.c		init_bins.c		main.c				\
	utils.c				builtin_env.c		builtin_setenv.c	builtin_unsetenv.c 
CFLAGS=-Wall -Wextra -Werror

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c
	gcc -g -c $< -o $@

$(LIB):
	make -C libft/ft_printf

$(NAME) : $(LIB) $(OBJ) minishell.h
	gcc -g $(OBJ) -L libft/ft_printf -lftprintf -o $(NAME)

clean:
	@/bin/rm -f $(OBJ)
	@make -C libft/ft_printf clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ft_printf fclean

re: fclean all

test:
	gcc -g test.c init_bins.c env_funcs.c errors.c hash_table.c utils.c -L libft/ft_printf -lftprintf -o test_binaries_size