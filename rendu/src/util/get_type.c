/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:32:36 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:32:37 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_type.h"

t_type	get_type(size_t size)
{
	if (size <= TINY_MAX)
		return (TINY);
	else if (size <= SMALL_MAX)
		return (SMALL);
	else
		return (LARGE);
}
