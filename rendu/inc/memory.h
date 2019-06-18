#ifndef MEMORY_H
# define MEMORY_H

/*
** struct s_memory
** size : total size with header
** isfree : status
*/

typedef struct	s_memory
{
	struct s_memory	*prev;
	size_t			size;
	bool			isfree;
	struct s_memory	*next;
}				t_memory;

# define ZONE_CAPACITY

# define TINY_MIN (1)
# define TINY_MAX (256)
# define TINY_ZONE (ZONE_CAPACITY * TINY_MAX)

# define SMALL_MIN (TINY_MAX + 1)
# define SMALL_MAX 1024
# define SMALL_ZONE (ZONE_CAPACITY * SMALL_MAX)

# define LARGE_MIN (SMALL_MAX + 1)

#endif
