/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:06:52 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:06:53 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_putaddr(void *ptr, t_ft_printf *args)
{
	args->params.flags |= FT_PRINTF_MASK_ALT_FORM
		| FT_PRINTF_MASK_ALT_FORM_FORCE;
	return (ft_printf_putunbr_base((unsigned long long int)ptr, args));
}
