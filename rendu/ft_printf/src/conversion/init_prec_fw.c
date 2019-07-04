/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prec_fw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:47:22 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:47:22 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

static bool	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_printf_atoi(const char **cursor)
{
	int	value;

	value = 0;
	while (**cursor && is_num(**cursor))
	{
		value = (value * 10) + (**cursor - '0');
		(*cursor)++;
	}
	return (value);
}

int			ft_printf_precision(const char **cursor,
	t_ft_printf_conv_params *params)
{
	if (**cursor != '.')
		return (0);
	(*cursor)++;
	params->flags |= FT_PRINTF_MASK_PRECISION;
	params->precision = ft_printf_atoi(cursor);
	return (1);
}

int			ft_printf_field_width(const char **cursor,
	t_ft_printf_conv_params *params)
{
	if (**cursor > '0' && **cursor <= '9')
	{
		params->f_width = ft_printf_atoi(cursor);
		return (1);
	}
	return (0);
}
