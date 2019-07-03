/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:05:37 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:05:42 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** ssize_t write(int fd, const void *buf, size_t count);
** void _exit(int status);
*/
# include <unistd.h>

/*
** void va_start(va_list ap, last);
** type va_arg(va_list ap, type);
** void va_end(va_list ap);
** void va_copy(va_list dest, va_list src);
*/
# include <stdarg.h>

/*
** typedef bool
*/
# include <stdbool.h>

/*
** INFINITY NAN
*/
# include <math.h>

# define FT_PRINTF_BUFSIZE 100

struct							s_ft_printf_ldouble
{
	long int					significand : 64;
	short int					exponent : 15;
	bool						sign : 1;
};

typedef union					u_ldouble
{
	long double					value;
	struct s_ft_printf_ldouble	cast;
}								t_ft_printf_ldouble;

typedef enum					e_ft_printf_type
{
	PTR,
	STR,
	U_CHARACTER,
	INTEGER,
	U_INTEGER,
	DOUBLE,
	PERCENT,
	UNKNOWN_TYPE
}								t_ft_printf_type;

typedef enum					e_ft_printf_modifier
{
	MOD_CHAR,
	MOD_SHORT,
	MOD_LONG,
	MOD_LONG_LONG,
	MOD_LONG_DOUBLE,
	NO_MODIFIER
}								t_ft_printf_modifier;

typedef struct					s_ft_printf_base
{
	unsigned int				base;
	bool						uppercase;
}								t_ft_printf_base;

# define FT_PRINTF_MASK_ALT_FORM_FORCE 0b1
# define FT_PRINTF_MASK_ALT_FORM 0b10
# define FT_PRINTF_MASK_PAD_LEFT 0b100
# define FT_PRINTF_MASK_ZERO_PAD 0b1000
# define FT_PRINTF_MASK_PLUS_SIGN 0b10000
# define FT_PRINTF_MASK_BLANK_SIGN 0b100000
# define FT_PRINTF_MASK_PRECISION 0b1000000

typedef struct					s_ft_printf_conv_params
{
	short						flags;
	int							f_width;
	int							precision;
	t_ft_printf_modifier		modifier;
	t_ft_printf_type			type;
	t_ft_printf_base			base;
}								t_ft_printf_conv_params;

typedef struct					s_ft_printf
{
	t_ft_printf_conv_params		params;
	va_list						ap;
	char						buf[FT_PRINTF_BUFSIZE];
}								t_ft_printf;

/*
** ft_printf
*/
int								ft_printf(const char *format, ...);

/*
** conversion
*/
void							ft_printf_format(const char *format,
	t_ft_printf *args, int *ret);
void							ft_printf_init_params(
	t_ft_printf_conv_params *params, const char **cursor);
int								ft_printf_type(const char **cursor,
	t_ft_printf_conv_params *params);
int								ft_printf_precision(const char **cursor,
	t_ft_printf_conv_params *params);
int								ft_printf_field_width(const char **cursor,
	t_ft_printf_conv_params *params);

int								ft_printf_conv_ptr(t_ft_printf *args);
int								ft_printf_conv_str(t_ft_printf *args);
int								ft_printf_conv_uchar(t_ft_printf *args);
int								ft_printf_conv_int(t_ft_printf *args);
int								ft_printf_conv_uint(t_ft_printf *args);
int								ft_printf_conv_double(t_ft_printf *args);

/*
** buf
*/
int								ft_printf_strlen(const char *str);
int								ft_printf_pad(const int srclen,
	t_ft_printf *args);
int								ft_printf_nappend(char dst[FT_PRINTF_BUFSIZE],
	const char *src, const int n);
int								ft_printf_append(char dst[FT_PRINTF_BUFSIZE],
	const char *src);
int								ft_printf_append_next(
	char dst[FT_PRINTF_BUFSIZE], const char *src);
void							ft_printf_clrbuf(char *buf);

int								ft_printf_putstr(const char *str,
	t_ft_printf *args);
int								ft_printf_putchar(const char *c,
	t_ft_printf *args);
int								ft_printf_putaddr(void *ptr, t_ft_printf *args);

int								ft_printf_print_sign(char **str,
	t_ft_printf *args);
int								ft_printf_itos(long long int value, short flags,
	char str[21]);

int								ft_printf_print_nbr(char *str,
	t_ft_printf *args);
int								ft_printf_putnbr(long long int value,
	t_ft_printf *args);
int								ft_printf_putunbr_base(
	unsigned long long int value, t_ft_printf *args);

int								ft_printf_print_sp_double(
	t_ft_printf_ldouble value, t_ft_printf *args);
int								ft_printf_print_double(char *int_part,
	char *dec_part, t_ft_printf *args);
int								ft_printf_putdouble(long double value,
	t_ft_printf *args);

#endif
