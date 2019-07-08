/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:32:12 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:32:13 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memcpy.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*srcs;
	size_t		i;

	if (!src || !dest)
		return (NULL);
	dst = dest;
	srcs = src;
	i = -1;
	while (++i < n)
		dst[i] = srcs[i];
	return ((void *)dst);
}
