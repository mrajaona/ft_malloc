/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:47:30 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:47:31 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

const char				g_init_convs[11] = {
	'c', 's', 'p', 'd', 'i',
	'o', 'u', 'x', 'X', 'f',
	'%'
};
const t_ft_printf_type	g_init_ft_printf_types[11] = {
	U_CHARACTER, STR, PTR, INTEGER, INTEGER,
	U_INTEGER, U_INTEGER, U_INTEGER, U_INTEGER, DOUBLE,
	PERCENT
};
const unsigned int		g_init_ft_printf_bases[11] = {
	0, 0, 16, 10, 10,
	8, 10, 16, 16, 10,
	0
};

int	ft_printf_type(const char **cursor, t_ft_printf_conv_params *params)
{
	unsigned int	i;

	i = 0;
	while (i < 11 && **cursor != g_init_convs[i])
		i++;
	if (i < 11)
	{
		params->type = g_init_ft_printf_types[i];
		params->base.base = g_init_ft_printf_bases[i];
		if (**cursor == 'X')
			params->base.uppercase = true;
		(*cursor)++;
		return (1);
	}
	return (0);
}
