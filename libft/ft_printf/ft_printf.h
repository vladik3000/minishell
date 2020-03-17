/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:00:04 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/01 16:40:03 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdint.h>

# define MINUS				1
# define PLUS				2
# define ZERO				4
# define SPACE				8
# define SHARP				16

# define H					2
# define HH					4
# define L					8
# define LL					16
# define D					32
# define BIGL				64

# define CHAR				512
# define STRING				4
# define POINTER			32
# define PERCENT			64
# define DECIMAL			10
# define OCTAL				8
# define UNSIGNED			128
# define HEX				16
# define BIG_HEX			17
# define FL					256
# define UNDEF				1024

# define ANSI_RED			"\x1b[31m"
# define ANSI_GREEN			"\x1b[32m"
# define ANSI_YELLOW		"\x1b[33m"
# define ANSI_BLUE			"\x1b[34m"
# define ANSI_CYAN			"\x1b[36m"
# define ANSI_RESET			"\x1b[0m"

# define MAX_LENGTH			4096

# define BASE				1000000000

typedef long long			t_ll;

typedef struct	s_num
{
	unsigned int	arr[100];
	unsigned		size_num;
}				t_num;

typedef unsigned long long	t_ull;

typedef struct	s_arr
{
	char		buff[5000];
	size_t		length;
}				t_arr;

typedef struct	s_float
{
	t_num			decimal;
	t_num			fractional;
	double			num;
	unsigned int	mantissa;
	int				exp;
	char			sign;
}				t_float;

typedef struct	s_ldbl
{
	t_num			decimal;
	t_num			fractional;
	long double		num;
	unsigned int	mantissa;
	int				exp;
	char			sign;
}				t_ldbl;

typedef struct	s_printf
{
	uint8_t		flag;
	t_ll		width;
	int			precision;
	uint16_t	size;
	uint64_t	type;
	size_t		length;
	char		buff[MAX_LENGTH + 1];
	va_list		ap;
	unsigned	printed;
	char		undef[2];
	int			fd;
}				t_printf;

int				ft_printf_fd(int fd, const char *format, ...);
void			get_width(t_printf *data, const char **format);
void			get_precision(t_printf *data, const char **format);
void			get_flags(t_printf *data, const char **format);
int				get_size(t_printf *data, const char **format);
int				ft_printf(const char *format, ...);
void			push_buffer(t_printf *data);
int				fill_options(t_printf *data, const char **format);
int				handle_overflow_buffer(t_printf *data, size_t len);
void			get_integer(t_printf *data, long long *n);
void			handle_integers(t_printf *data);
void			utoa_base_buff_ox(t_ull value, unsigned base, t_printf *data);
void			itoa_base_buff(t_ll value, unsigned base, t_printf *data);
char			neg_value(t_ll value, unsigned base, t_printf *data);
char			pos_value(t_ll value, unsigned base, t_printf *data);
char			result(t_ll value, unsigned base, t_printf *data);
t_ll			new_value(t_ll value, unsigned *base, t_ll *val);
size_t			ft_unumlen(t_ull val, unsigned base);
void			itoa_base_buff_u(t_ull value, t_printf *data);
void			get_unsigned(t_printf *data, t_ull *n);
size_t			ft_numlen_u(t_ull val);
void			handle_unsigned(t_printf *data);
void			handle_floats(t_printf *data);
void			handle_octals(t_printf *data);
void			handle_hexdecimals(t_printf *data);
void			handle_bighex(t_printf *data);
void			handle_chars(t_printf *data);
void			handle_strings(t_printf *data);
void			handle_pointers(t_printf *data);
void			handle_uoctal(t_printf *data);
void			handle_ubighex(t_printf *data);
void			handle_uhex(t_printf *data);
void			add_long_short(t_num *a, unsigned b);
void			multiply_long_short(t_num *a, unsigned b);
void			add_long_long(t_num *a, t_num b);
t_num			big_power_of_five(unsigned power);
void			ftoa_base_buff(unsigned int value, t_arr *arr);
void			print_float(t_arr *dec, t_arr *frac, t_printf *data, int i);
void			before_print_float(t_float number, t_printf *data);
int				count_zeros(t_float *n);
int				count_zeros_ldbl(t_ldbl *n);
int				handle_f_prec(t_arr *arr, t_arr *dec, t_printf *data);
int				handle_f_dec(t_arr *arr, char num, char flag);
void			before_print_ldbl(t_ldbl number, t_printf *data);
int				reset_color(t_printf *data, const char **f);
int				read_color(t_printf *data, const char **f);

#endif
