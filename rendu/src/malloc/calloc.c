/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:01:01 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/11 10:01:01 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ls marche si on vire calloc du Makefile
// vim marche avec le patch realloc
#include "calloc.h"

void	*calloc_thread(size_t count, size_t size)
{
	char	*ptr;
	size_t	full_size;

	full_size = count * size;
	ptr = (char *)malloc_thread(full_size);
	if (ptr)
	{
		full_size = malloc_size_thread(ptr);
		while (full_size)
		{
			full_size--;
			ptr[full_size] = 0;
		}
	}
	return (ptr);
}

#include "ft_printf.h" // debug
#include "malloc_size.h" // debug

void	*calloc(size_t count, size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex) != 0)
		return (NULL);
	ft_printf("%-10s : %llu (%llu x %llu)\n", // debug
		"calloc", count * size, count, size); // debug
	ret = calloc_thread(count, size);
	ft_printf("%-10s : %llu %p\n", ">>", malloc_size_thread(ret), ret); // debug
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
