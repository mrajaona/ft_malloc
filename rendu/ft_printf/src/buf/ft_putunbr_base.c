/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:07:42 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:07:43 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

/*
** MAX 1777777777777777777777 // 22c + '\0'
*/

int	ft_printf_putunbr_base(unsigned long long int value, t_ft_printf *args)
{
	char	s[23];
	int		i;

	if (args->params.base.base == 0)
		return (0);
	args->params.flags = args->params.flags
		& ~(FT_PRINTF_MASK_PLUS_SIGN | FT_PRINTF_MASK_BLANK_SIGN);
	s[22] = '\0';
	i = 21;
	if (value == 0)
		s[i] = '0';
	while (i >= 0 && value)
	{
		s[i] = value % args->params.base.base;
		if (s[i] >= 0 && s[i] <= 16)
		{
			if (s[i] > 9)
				s[i] = s[i] - 10 + (args->params.base.uppercase ? 'A' : 'a');
			else
				s[i] += '0';
		}
		value /= args->params.base.base;
		i = value ? (i - 1) : i;
	}
	return (ft_printf_print_nbr(s + i, args));
}
