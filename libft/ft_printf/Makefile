# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 16:06:00 by fmallist          #+#    #+#              #
#    Updated: 2020/08/08 20:15:29 by fmallist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFTA = libft.a
SRCS = buffer_mgmt.c ft_printf.c fill_options.c itoa_base_buff.c handle_overflow_buffer.c get_integer.c handle_integers.c \
		itoa_base_extra_funcs.c itoa_base_buff_u.c handle_unsigned.c get_unsigned.c ftoa.c ftoa_base_buff.c \
		printing_floats.c long_arithmetics.c handle_octals.c handle_hexdecimals.c handle_bighex.c \
		get_specifiers.c handle_floats.c handle_csp.c fill_ldbl_arrays.c fill_float_arrays.c \
		hanlde_uhex.c handle_ubighex.c handle_uoctal.c utoa_base_buff_ox.c handle_strings.c bonuses.c
OBJ = $(SRCS:.c=.o)
LIBDIR = ../
LIBNAME = ../libft.a
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

LIB:
	make -C ../

$(OBJ): %.o: %.c ft_printf.h ../libft.a
	@gcc -c $(CFLAGS) $< -o $@

$(NAME): LIB $(OBJ) 
	@cp ../libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)
clean:
	@/bin/rm -rf $(OBJ)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -rf libftprintf.a
	@make -C $(LIBDIR) fclean

re: fclean all
