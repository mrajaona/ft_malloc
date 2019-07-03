/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:26:49 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:26:50 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_conv_int(t_ft_printf *args)
{
	long long int	value;

	if (args->params.modifier == MOD_LONG_LONG)
		value = va_arg(args->ap, long long int);
	else if (args->params.modifier == MOD_LONG)
		value = va_arg(args->ap, long int);
	else if (args->params.modifier == MOD_SHORT)
		value = (short)va_arg(args->ap, int);
	else if (args->params.modifier == MOD_CHAR)
		value = (char)va_arg(args->ap, int);
	else
		value = va_arg(args->ap, int);
	return (ft_printf_putnbr(value, args));
}
