/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:01:09 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 10:01:10 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reallocf.h"

void	*reallocf_thread(void *ptr, size_t size)
{
	void *nptr;

	if (!(nptr = realloc_thread(ptr, size)))
		free_thread(ptr);
	return (nptr);
}

#include "ft_printf.h"
#include "malloc_size.h"

void	*reallocf(void *ptr, size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	// ft_printf("%-10s : %llu %p (%llu)\n", "reallocf", size, ptr, malloc_size_thread(ptr));
	ret = reallocf_thread(ptr, size);
	// ft_printf("%-10s : %llu %p\n", ">>", malloc_size_thread(ret), ret);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
