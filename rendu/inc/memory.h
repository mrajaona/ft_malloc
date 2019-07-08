/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:28:04 by mrajaona          #+#    #+#             */
/*   Updated: 2019/07/08 13:28:05 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stddef.h>

/*
** size : available size (not including header)
** isfree : status
** addr : start of available memory
*/

typedef struct	s_elem_info
{
	struct s_elem_info	*prev;
	struct s_elem_info	*next;
	size_t				size;
	char				isfree;
	void				*addr;
}				t_elem_info;

/*
** size : available size (not including header)
** first : address of the first element in the zone
*/

typedef struct	s_zone_info
{
	struct s_zone_info	*prev;
	struct s_zone_info	*next;
	size_t				size;
	t_elem_info			*first;
}				t_zone_info;

# define ZONE_CAPACITY (100)

# define TINY_MIN (1)
# define TINY_MAX (1 << 15)

# define SMALL_MIN (TINY_MAX + 1)
# define SMALL_MAX (1 << 20)

# define LARGE_MIN (SMALL_MAX + 1)

typedef enum	e_type
{
	TINY,
	SMALL,
	LARGE
}				t_type;

# define MMAP_PROT (PROT_READ | PROT_WRITE | PROT_EXEC)
# define MMAP_FLAG (MAP_ANONYMOUS | MAP_PRIVATE)

#endif
