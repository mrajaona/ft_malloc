/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:07:06 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:07:07 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				check_neg_zero(long long int dec_part,
	t_ft_printf *args)
{
	char	*int_str;
	char	dec_str[21];
	int		dec_i;

	int_str = "-0";
	dec_i = ft_printf_itos(dec_part, 0, dec_str);
	return (ft_printf_print_double(int_str, dec_str + dec_i, args));
}

static int				ft_dtos(long long int int_part,
	long long int dec_part, t_ft_printf *args)
{
	char	int_str[21];
	int		int_i;
	char	dec_str[21];
	int		dec_i;

	int_i = ft_printf_itos(int_part, args->params.flags, int_str);
	dec_i = ft_printf_itos(dec_part, 0, dec_str);
	return (ft_printf_print_double(int_str + int_i, dec_str + dec_i, args));
}

static long long int	ft_pow_ten(int exponent)
{
	long long int	res;

	res = 1;
	while (exponent)
	{
		res *= 10;
		exponent += exponent > 0 ? -1 : 1;
	}
	return (res);
}

int						ft_printf_putdouble(long double value,
	t_ft_printf *args)
{
	t_ft_printf_ldouble		v;
	long long int			int_part;
	long long int			dec_part;
	unsigned long long int	precision;
	short int				exponent;

	v.value = value;
	exponent = v.cast.exponent & 0x7FFF;
	if (exponent == 0x7FFF)
		return (ft_printf_print_sp_double(v, args));
	if (!(args->params.flags & FT_PRINTF_MASK_PRECISION))
	{
		args->params.flags |= FT_PRINTF_MASK_PRECISION;
		args->params.precision = 6;
	}
	precision = ft_pow_ten(args->params.precision);
	int_part = value;
	dec_part = ((value < 0.0L) ? -1 : 1) * (value - int_part) * precision;
	if (int_part == 0 && v.cast.sign)
		return (check_neg_zero(dec_part, args));
	else
		return (ft_dtos(int_part, dec_part, args));
}
