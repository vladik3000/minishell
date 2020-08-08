# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 16:05:25 by fmallist          #+#    #+#              #
#    Updated: 2020/08/08 18:46:03 by fmallist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
LIB=libft/libftprintf.a
SRC=builtin_cd.c		builtin_echo.c		builtin_execution.c \
	builtin_exit.c		env_funcs.c			errors.c			\
	hash_table.c		init_bins.c			main.c				\
	utils.c				utils_2.c			hash_table_2.c		\
	builtin_env.c		builtin_setenv.c	builtin_unsetenv.c	\
	echo_funcs.c		env_funcs_2.c		setenv_funcs.c		\
	hash_table_3.c		

CFLAGS=-Wall -Wextra -Werror
OBJDIR=obj/
SRCDIR=src/
OBJ=$(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(LIB) $(NAME)

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p obj
	gcc $(CFLAGS) -c $< -o $@

$(LIB):
	make -C libft/ft_printf

$(NAME) : $(OBJ) minishell.h
	gcc $(CFLAGS) $(OBJ) -L libft/ft_printf -lftprintf -o $(NAME)

clean:
	@/bin/rm -rf $(OBJ)
	@make -C libft/ft_printf clean

fclean: clean
	@/bin/rm -rf $(NAME) obj
	@make -C libft/ft_printf fclean

re: fclean all

test:
	gcc -g test.c init_bins.c env_funcs.c errors.c hash_table.c utils.c -L libft/ft_printf -lftprintf -o test_binaries_size
