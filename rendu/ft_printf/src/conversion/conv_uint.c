/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:27:28 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:27:29 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

int	ft_printf_conv_uint(t_ft_printf *args)
{
	unsigned long long int	value;

	if (args->params.modifier == MOD_LONG_LONG)
		value = va_arg(args->ap, unsigned long long int);
	else if (args->params.modifier == MOD_LONG)
		value = va_arg(args->ap, unsigned long int);
	else if (args->params.modifier == MOD_SHORT)
		value = (unsigned short)va_arg(args->ap, unsigned int);
	else if (args->params.modifier == MOD_CHAR)
		value = (unsigned char)va_arg(args->ap, unsigned int);
	else
		value = va_arg(args->ap, unsigned int);
	return (ft_printf_putunbr_base(value, args));
}
