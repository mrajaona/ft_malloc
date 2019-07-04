/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:27:36 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:27:37 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

const t_ft_printf_type	g_convert_ft_printf_types[6] = {
	PTR, STR, U_CHARACTER, INTEGER, U_INTEGER, DOUBLE
};
int				(*const g_convert_fn[6])(t_ft_printf *args) = {
	&ft_printf_conv_ptr,
	&ft_printf_conv_str,
	&ft_printf_conv_uchar,
	&ft_printf_conv_int,
	&ft_printf_conv_uint,
	&ft_printf_conv_double
};

static int	ft_convert(const char **cursor, t_ft_printf *args)
{
	int		i;

	(*cursor)++;
	if (!*(*cursor))
		return (0);
	else
	{
		ft_printf_init_params(&(args->params), cursor);
		if (args->params.type == UNKNOWN_TYPE && *cursor && **cursor)
		{
			i = ft_printf_putchar(*cursor, args);
			(*cursor)++;
			return (i);
		}
		else if (args->params.type == PERCENT)
			return (ft_printf_putchar("%", args));
		i = 0;
		while (i < 6 && g_convert_ft_printf_types[i] != args->params.type)
			i++;
		if (i == 6)
			return (0);
		return (g_convert_fn[i](args));
	}
	return (0);
}

void		ft_printf_format(const char *format, t_ft_printf *args, int *ret)
{
	const char			*cursor;
	int					tmp;

	ft_printf_clrbuf(args->buf);
	cursor = format;
	tmp = 0;
	while (*cursor)
	{
		if (*cursor == '%')
			tmp = ft_convert(&cursor, args);
		else
		{
			tmp = ft_printf_append_next(args->buf, cursor);
			cursor += tmp;
		}
		*ret += tmp;
	}
	write(1, args->buf, ft_printf_strlen(args->buf));
}
