/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:07:27 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:07:27 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_srclen(const char *str, t_ft_printf *args)
{
	int	len;

	len = ft_printf_strlen(str);
	if ((args->params.flags & FT_PRINTF_MASK_PRECISION)
		&& args->params.precision < len)
		return (args->params.precision);
	else
		return (len);
}

int			ft_printf_putstr(const char *str, t_ft_printf *args)
{
	int	ret;
	int	srclen;

	ret = 0;
	srclen = ft_get_srclen(str ? str : "(null)", args);
	if (!(args->params.flags & FT_PRINTF_MASK_PAD_LEFT))
		ret += ft_printf_pad(srclen, args);
	if (args->params.flags & FT_PRINTF_MASK_PRECISION)
		ret += ft_printf_nappend(args->buf, str ? str : "(null)",
			args->params.precision);
	else
		ret += ft_printf_append(args->buf, str ? str : "(null)");
	if (args->params.flags & FT_PRINTF_MASK_PAD_LEFT)
		ret += ft_printf_pad(srclen, args);
	return (ret);
}
