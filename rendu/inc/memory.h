#ifndef MEMORY_H
# define MEMORY_H

/*
** size : available size
** isfree : status
** addr : start of available memory
*/

typedef struct	s_info
{
	void	*addr;
	size_t	size;
	bool	isfree;
}				t_info;

# define ZONE_CAPACITY (100)

# define TINY_MIN (1)
# define TINY_MAX (256)
# define TINY_ZONE_SIZE (ZONE_CAPACITY * TINY_MAX)
# define TINY_MAX_CAPACITY (TINY_ZONE_SIZE / TINY_MIN)

# define SMALL_MIN (TINY_MAX + 1)
# define SMALL_MAX (1024)
# define SMALL_ZONE_SIZE (ZONE_CAPACITY * SMALL_MAX)
# define SMALL_MAX_CAPACITY (SMALL_ZONE_SIZE / SMALL_MIN)

# define LARGE_MIN (SMALL_MAX + 1)

#endif
