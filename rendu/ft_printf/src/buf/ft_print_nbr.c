/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:06:38 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:06:39 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

int			ft_printf_print_sign(char **str, t_ft_printf *args)
{
	int		ret;

	ret = 0;
	if (args->params.type == INTEGER && ((*str)[0] < '0' || (*str)[0] > '9'))
	{
		ret += ft_printf_nappend(args->buf, *str, 1);
		(*str)++;
	}
	return (ret);
}

/*
**	o : prepend a "0" if first char was not zero already.
**	x : if nonzero, prepend "0x"
**	X : if nonzero, prepend "0X"
*/

static char	*ft_get_alter(char *str, t_ft_printf *args, int srclen,
	int len)
{
	if (args->params.flags & FT_PRINTF_MASK_ALT_FORM)
	{
		if (args->params.base.base == 8)
		{
			if (!str)
				return ("0");
			else if ((args->params.flags & FT_PRINTF_MASK_ZERO_PAD)
				&& !(args->params.flags & FT_PRINTF_MASK_PAD_LEFT))
				return (NULL);
			else if (len < srclen)
				return (NULL);
			else
				return ((str[0] == '0') ? NULL : "0");
		}
		else if (args->params.base.base == 16 && ((str && str[0] != '0')
				|| args->params.flags & FT_PRINTF_MASK_ALT_FORM_FORCE))
			return (args->params.base.uppercase ? "0X" : "0x");
	}
	return (NULL);
}

static int	ft_put_precision(t_ft_printf *args, int len, int srclen)
{
	int		ret;

	ret = 0;
	if (args->params.precision)
	{
		while (srclen > len)
		{
			ret += ft_printf_append(args->buf, "0");
			len++;
		}
	}
	return (ret);
}

static int	ft_print_nbr(char *str, t_ft_printf *args, int len, int srclen)
{
	char	*alter;
	int		ret;

	ret = 0;
	alter = ft_get_alter(str, args, srclen, len);
	if (!(args->params.flags & FT_PRINTF_MASK_PAD_LEFT)
		&& !(args->params.flags & FT_PRINTF_MASK_ZERO_PAD))
		ret += ft_printf_pad(srclen + ft_printf_strlen(alter), args);
	if (str)
		ret += ft_printf_print_sign(&str, args);
	if (alter)
		ret += ft_printf_append(args->buf, alter);
	if (!(args->params.flags & FT_PRINTF_MASK_PAD_LEFT)
		&& (args->params.flags & FT_PRINTF_MASK_ZERO_PAD))
		ret += ft_printf_pad(srclen + ft_printf_strlen(alter), args);
	ret += ft_put_precision(args, len, srclen);
	ret += ft_printf_append(args->buf, str);
	if (args->params.flags & FT_PRINTF_MASK_PAD_LEFT)
		ret += ft_printf_pad(srclen + ft_printf_strlen(alter), args);
	return (ret);
}

int			ft_printf_print_nbr(char *str, t_ft_printf *args)
{
	int		len;
	int		sign;
	int		srclen;

	if (args->params.flags & FT_PRINTF_MASK_PRECISION
		&& args->params.precision == 0 && str[0] == '0')
		return (ft_print_nbr(NULL, args, 0, 0));
	else
	{
		len = ft_printf_strlen(str);
		if (str[0] == '+' || str[0] == '-' || str[0] == ' ')
			sign = 1;
		else
			sign = 0;
		if (args->params.flags & FT_PRINTF_MASK_PRECISION)
			args->params.flags &= ~(FT_PRINTF_MASK_ZERO_PAD);
		if ((args->params.flags & FT_PRINTF_MASK_PRECISION)
			&& args->params.precision > (len - sign))
			srclen = args->params.precision + sign;
		else
			srclen = len;
	}
	return (ft_print_nbr(str, args, len, srclen));
}
