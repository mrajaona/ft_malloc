/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:26:39 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:26:40 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_conv_double(t_ft_printf *args)
{
	long double	value;

	if (args->params.modifier == MOD_LONG_DOUBLE)
		value = va_arg(args->ap, long double);
	else
		value = va_arg(args->ap, double);
	return (ft_printf_putdouble(value, args));
}
