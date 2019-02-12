#ifndef FT_MALLOC_H
# define FT_MALLOC_H

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
** malloc(1 - n) -> TINY
** malloc(n+1 - m) -> SMALL
** malloc(>= m+1) -> LARGE (hors zone == mmap())
*/
enum	e_page
{
	TINY,
	SMALL,
	LARGE
};

# define TINY_SIZE_MAX (1 << 6)
# define TINY_N_MAX 100

# define SMALL_SIZE_MAX (1 << 10)
# define SMALL_N_MAX 100

/*
** type : type of allocation
** size : allocated size in bytes (not including identifier)
** prev : NULL | address of previous identifier
** next : NULL | address of next identifier
*/
typedef struct	s_identifier
{
	enum e_page			type;
	size_t				size;
	struct s_identifier	*prev;
	struct s_identifier	*next;
}				t_identifier;

/*
** type : type of allocation
** size : allocated size in bytes (including identifier)
** lst_alloc : NULL | addr of first allocated identifier
** lst_free : NULL | addr of first free identifier
*/
typedef struct	s_zone_id
{
	enum e_page		type;
	size_t			size;
	t_identifier	*lst_alloc;
	t_identifier	*lst_free;
}				t_zone_id;

/*
** list of mapped zones
** type : type of allocation
** prev : NULL | address of previous zone
** next : NULL | address of next zone
*/
typedef struct	s_map_list
{
	enum e_page			type;
	struct s_identifier	*prev;
	struct s_identifier	*next;
}				t_map_list;

size_t	align(size_t size);

void	free(void *ptr);

void	*malloc(size_t size);

void	*realloc(void *ptr, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);

void	show_mem_alloc();

#endif
