/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:27:10 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:27:11 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_conv_str(t_ft_printf *args)
{
	void	*str;

	str = va_arg(args->ap, char *);
	return (ft_printf_putstr(str, args));
}
