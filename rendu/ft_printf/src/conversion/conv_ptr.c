/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:27:01 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:27:01 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_conv_ptr(t_ft_printf *args)
{
	void	*ptr;

	ptr = va_arg(args->ap, void *);
	return (ft_printf_putaddr(ptr, args));
}
