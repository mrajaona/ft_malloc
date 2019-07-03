/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:07:27 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:07:27 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_putchar(const char *c, t_ft_printf *args)
{
	int	ret;

	ret = 0;
	if (!(args->params.flags & FT_PRINTF_MASK_PAD_LEFT))
		ret += ft_printf_pad(1, args);
	if (c[0] != 0)
		ret += ft_printf_nappend(args->buf, c, 1);
	else
	{
		write(1, args->buf, ft_printf_strlen(args->buf));
		ft_printf_clrbuf(args->buf);
		write(1, c, 1);
		ret += 1;
	}
	if (args->params.flags & FT_PRINTF_MASK_PAD_LEFT)
		ret += ft_printf_pad(1, args);
	return (ret);
}
