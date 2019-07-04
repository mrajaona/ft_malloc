/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_uchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:27:21 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:27:22 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

int	ft_printf_conv_uchar(t_ft_printf *args)
{
	char	c[2];

	c[0] = (char)va_arg(args->ap, int);
	c[1] = '\0';
	return (ft_printf_putchar(c, args));
}
