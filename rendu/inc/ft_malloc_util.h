#ifndef FT_MALLOC_UTIL_H
# define FT_MALLOC_UTIL_H

# include <sys/mman.h>
/*
** void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
** int munmap(void *addr, size_t length);
*/

# include <unistd.h>
/*
** int getpagesize(void);
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include <sys/mman.h>
/*
** void *mmap(void *addr, size_t length, int prot,
**     int flags, int fd, off_t offset);
** int munmap(void *addr, size_t length);
*/

# include <sys/time.h>
# include <sys/resource.h>
/*
** int getrlimit(int resource, struct rlimit *rlim);
*/

# include <pthread.h>

/*
** bool type
*/
# include <stdbool.h>

# include "malloc.h"

# define MMAP_PROT PROT_READ | PROT_WRITE
# define MMAP_FLAGS MAP_ANONYMOUS | MAP_PRIVATE // LINUX
// # define MMAP_FLAGS MAP_ANON | MAP_PRIVATE // MAC_OS
# define MMAP_FD -1
# define MMAP_OFFSET 0

/*
** au moins 100 allocations par zone
** N >= 100n
** M >= 100m
** 
** malloc(1 ~ n) -> TINY
** malloc(n+1 ~ m) -> SMALL
** malloc(>= m+1) -> LARGE (hors zone == mmap())
*/
enum	e_type
{
	TINY,
	SMALL,
	LARGE
};

# define TINY_SIZE_MIN 1
# define TINY_SIZE_MAX (1 << 6)
# define TINY_N 100

# define SMALL_SIZE_MIN (TINY_SIZE_MIN + 1)
# define SMALL_SIZE_MAX (1 << 10)
# define SMALL_N 100

# define LARGE_SIZE_MIN (SMALL_SIZE_MAX + 1)

/*
** type : type of allocation
** addr : adress returned to user
** size : allocated size in bytes (including header)
** isfree : returns true if data is free
** prev : NULL | address of previous identifier
** next : NULL | address of next identifier
*/
typedef struct	s_block_id
{
	enum e_type			type;
	void				*addr;
	size_t				size;
	bool				isfree;
	struct s_block_id	*prev;
	struct s_block_id	*next;
}				t_chunk_id;

/*
** size	: size of zone (including header)
** lst_ids	: list of chunks in zone
** prev : NULL | address of previous zone
** next : NULL | address of next zone
*/
typedef struct	s_zone_id
{
	size_t				size;
	struct s_zone_id	*prev;
	struct s_zone_id	*next;
}				t_zone_id;

/*
** store adresses of first zones
*/
extern t_zone_id	*g_lst_tiny;
extern t_zone_id	*g_lst_small;
extern t_chunk_id	*g_lst_large;

void		merge(t_chunk_id *first, t_chunk_id *second);

size_t		mmap_align(size_t size);
size_t		chunk_align(size_t size);

t_chunk_id	*identify(void *ptr);

void		*ft_memcpy(void *dest, const void *src, size_t n);


#endif
