/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:47:17 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:47:18 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	overriden_flag(char c, t_ft_printf_conv_params *params)
{
	if (c == '0')
	{
		if (!(params->flags & FT_PRINTF_MASK_PAD_LEFT))
			params->flags |= FT_PRINTF_MASK_ZERO_PAD;
	}
	else if (c == ' ')
	{
		if (!(params->flags & FT_PRINTF_MASK_PLUS_SIGN))
			params->flags |= FT_PRINTF_MASK_BLANK_SIGN;
	}
}

static int	check_flags(const char **cursor, t_ft_printf_conv_params *params)
{
	if (**cursor == '#')
		params->flags |= FT_PRINTF_MASK_ALT_FORM;
	else if (**cursor == '0')
		overriden_flag(**cursor, params);
	else if (**cursor == '-')
	{
		params->flags |= FT_PRINTF_MASK_PAD_LEFT;
		params->flags &= ~(FT_PRINTF_MASK_ZERO_PAD);
	}
	else if (**cursor == ' ')
		overriden_flag(**cursor, params);
	else if (**cursor == '+')
	{
		params->flags |= FT_PRINTF_MASK_PLUS_SIGN;
		params->flags &= ~(FT_PRINTF_MASK_BLANK_SIGN);
	}
	else
		return (0);
	(*cursor)++;
	return (1);
}

static int	check_modifier(const char **cursor,
	t_ft_printf_conv_params *params)
{
	if (**cursor == 'L')
		params->modifier = MOD_LONG_DOUBLE;
	else if (**cursor == 'h')
	{
		if (params->modifier == MOD_SHORT)
			params->modifier = MOD_CHAR;
		else
			params->modifier = MOD_SHORT;
	}
	else if (**cursor == 'l')
	{
		if (params->modifier == MOD_LONG)
			params->modifier = MOD_LONG_LONG;
		else
			params->modifier = MOD_LONG;
	}
	else
		return (0);
	(*cursor)++;
	return (1);
}

void		ft_printf_init_params(t_ft_printf_conv_params *params,
	const char **cursor)
{
	params->flags = 0;
	params->f_width = 0;
	params->precision = 0;
	params->modifier = NO_MODIFIER;
	params->type = UNKNOWN_TYPE;
	params->base.base = 10;
	params->base.uppercase = false;
	while (*cursor && **cursor && params->type == UNKNOWN_TYPE)
	{
		if (check_flags(cursor, params))
			continue ;
		if (ft_printf_field_width(cursor, params))
			continue ;
		if (ft_printf_precision(cursor, params))
			continue ;
		if (check_modifier(cursor, params))
			continue ;
		if (!ft_printf_type(cursor, params))
			return ;
	}
}
