/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 10:06:05 by mrajaona          #+#    #+#             */
/*   Updated: 2019/03/21 10:06:08 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_util.h"

int		ft_printf_pad(const int srclen, t_ft_printf *args)
{
	int		pad;
	int		ret;

	pad = args->params.f_width;
	ret = 0;
	while (pad > srclen)
	{
		ret += ft_printf_append(args->buf, args->params.flags
			& FT_PRINTF_MASK_ZERO_PAD ? "0" : " ");
		pad--;
	}
	return (ret);
}

int		ft_printf_nappend(char dst[FT_PRINTF_BUFSIZE],
	const char *src, const int n)
{
	int		i;
	size_t	j;

	if (!dst || !src)
		return (0);
	i = 0;
	j = ft_printf_strlen(dst);
	while (src[i] && i < n)
	{
		if (j == FT_PRINTF_BUFSIZE - 1)
		{
			write(1, dst, FT_PRINTF_BUFSIZE - 1);
			ft_printf_clrbuf(dst);
			j = 0;
		}
		dst[j] = src[i];
		i++;
		j++;
	}
	return (i);
}

int		ft_printf_append(char dst[FT_PRINTF_BUFSIZE], const char *src)
{
	size_t	i;
	size_t	j;

	if (!dst || !src)
		return (0);
	i = 0;
	j = ft_printf_strlen(dst);
	while (src[i])
	{
		if (j == FT_PRINTF_BUFSIZE - 1)
		{
			write(1, dst, FT_PRINTF_BUFSIZE - 1);
			ft_printf_clrbuf(dst);
			j = 0;
		}
		dst[j] = src[i];
		i++;
		j++;
	}
	return (i);
}

int		ft_printf_append_next(char dst[FT_PRINTF_BUFSIZE], const char *src)
{
	int		i;
	size_t	j;

	if (!dst || !src)
		return (0);
	i = 0;
	j = ft_printf_strlen(dst);
	while (src[i] && src[i] != '%')
	{
		if (j == FT_PRINTF_BUFSIZE - 1)
		{
			write(1, dst, FT_PRINTF_BUFSIZE - 1);
			ft_printf_clrbuf(dst);
			j = 0;
		}
		dst[j] = src[i];
		i++;
		j++;
	}
	return (i);
}

void	ft_printf_clrbuf(char *buf)
{
	size_t	i;

	i = 0;
	while (i < FT_PRINTF_BUFSIZE)
	{
		buf[i] = 0;
		i++;
	}
}
