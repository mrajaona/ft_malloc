/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:06:22 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:06:25 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

static int	ft_put_precision(t_ft_printf *args, char *dec_part)
{
	int		i;
	int		ret;
	int		len;

	ret = 0;
	i = 0;
	if (args->params.precision)
	{
		ret += ft_printf_append(args->buf, ".");
		len = ft_printf_strlen(dec_part);
		while (i + len < args->params.precision)
		{
			ret += ft_printf_append(args->buf, "0");
			i++;
		}
		i = ft_printf_nappend(args->buf, dec_part, args->params.precision);
		ret += i;
	}
	return (ret);
}

static int	ft_pad_sp(t_ft_printf_ldouble v, t_ft_printf *args)
{
	int		ret;

	ret = 0;
	if (v.value == INFINITY || v.value == -INFINITY)
	{
		if (v.cast.sign)
			ret += ft_printf_append(args->buf, "-");
		else if (args->params.flags
			& (FT_PRINTF_MASK_PLUS_SIGN | FT_PRINTF_MASK_BLANK_SIGN))
			ret += ft_printf_append(args->buf,
				args->params.flags & FT_PRINTF_MASK_PLUS_SIGN ? "+" : " ");
	}
	else if (args->params.flags
		& (FT_PRINTF_MASK_PLUS_SIGN | FT_PRINTF_MASK_BLANK_SIGN))
		ret += ft_printf_append(args->buf, " ");
	return (ret);
}

int			ft_printf_print_sp_double(t_ft_printf_ldouble v, t_ft_printf *args)
{
	int		ret;
	char	*str;
	int		srclen;

	ret = 0;
	str = (v.value == INFINITY || v.value == -INFINITY) ? "inf" : "nan";
	srclen = ft_printf_strlen(str);
	if (v.cast.sign
		|| args->params.flags
			& (FT_PRINTF_MASK_PLUS_SIGN | FT_PRINTF_MASK_BLANK_SIGN))
		srclen++;
	args->params.flags &= (FT_PRINTF_MASK_PAD_LEFT | FT_PRINTF_MASK_PLUS_SIGN
		| FT_PRINTF_MASK_BLANK_SIGN);
	if (!(args->params.flags & FT_PRINTF_MASK_PAD_LEFT))
		ret += ft_printf_pad(srclen, args);
	ret += ft_pad_sp(v, args);
	ret += ft_printf_append(args->buf, str);
	if (args->params.flags & FT_PRINTF_MASK_PAD_LEFT)
		ret += ft_printf_pad(srclen, args);
	return (ret);
}

int			ft_printf_print_double(char *i_part, char *d_part,
	t_ft_printf *args)
{
	int		ret;
	int		srclen;

	ret = 0;
	srclen = ft_printf_strlen(i_part);
	if ((args->params.flags & FT_PRINTF_MASK_PRECISION)
		&& args->params.precision > 0)
		srclen += args->params.precision + 1;
	else if (args->params.flags & FT_PRINTF_MASK_ALT_FORM)
		srclen += 1;
	if (!(args->params.flags & FT_PRINTF_MASK_PAD_LEFT))
		ret += ft_printf_pad(srclen, args);
	ret += ft_printf_print_sign(&i_part, args);
	ret += ft_printf_append(args->buf, i_part);
	if (args->params.flags & FT_PRINTF_MASK_ALT_FORM)
		ret += ft_printf_append(args->buf, ".");
	else
		ret += ft_put_precision(args, d_part);
	if (args->params.flags & FT_PRINTF_MASK_PAD_LEFT)
		ret += ft_printf_pad(srclen, args);
	return (ret);
}
