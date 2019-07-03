/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:51:55 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:52:03 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int			ret;
	t_ft_printf	args;

	if (!format)
		return (0);
	va_start(args.ap, format);
	ret = 0;
	ft_printf_format(format, &args, &ret);
	va_end(args.ap);
	return (ret);
}
