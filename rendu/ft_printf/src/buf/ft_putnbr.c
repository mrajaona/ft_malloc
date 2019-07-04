/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:07:21 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:07:21 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

int	ft_printf_itos(long long int value, short flags, char str[21])
{
	int		i;
	bool	negative;

	str[20] = '\0';
	i = 19;
	negative = value < 0 ? true : false;
	if (value == 0)
		str[i] = '0';
	while (i >= 1 && value)
	{
		str[i] = ((negative ? -1 : 1) * (value % 10)) + '0';
		value /= 10;
		i = value ? (i - 1) : i;
	}
	if (negative)
	{
		i--;
		str[i] = '-';
	}
	else if (flags & (FT_PRINTF_MASK_PLUS_SIGN | FT_PRINTF_MASK_BLANK_SIGN))
	{
		i--;
		str[i] = flags & FT_PRINTF_MASK_PLUS_SIGN ? '+' : ' ';
	}
	return (i);
}

/*
** MIN −9,223,372,036,854,775,808
** MAX +9,223,372,036,854,775,807
** sign + 19c + '\0'
*/

int	ft_printf_putnbr(long long int value, t_ft_printf *args)
{
	char	str[21];
	int		i;

	args->params.flags = args->params.flags & ~(FT_PRINTF_MASK_ALT_FORM);
	i = ft_printf_itos(value, args->params.flags, str);
	return (ft_printf_print_nbr(str + i, args));
}
