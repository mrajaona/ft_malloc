#ifndef FT_MALLOC_PRINT_H
# define FT_MALLOC_PRINT_H

# include <stddef.h>
/*
** size_t
*/

# include <unistd.h>
/*
** ssize_t write(int fd, const void *buf, size_t count);
*/

#include "ft_malloc_util.h"

/*
** std
*/

# define STDOUT 1
# define STDERR 2

/*
** define text for output
*/

# define HEAD_TINY "TINY"
# define HEAD_SMALL "SMALL"
# define HEAD_LARGE "LARGE"
# define HEAD_TOTAL "Total"
# define HEAD_HEX "0x"

# define SEP_ADDR " - "
# define SEP_DATA " : "

# define UNIT " octets"

# define BASE_STR "0123456789ABCDEF"

/*
** Messages
*/

# define ERR_UNKNOWN_TYPE "Error: unknown type detected"

/*
** more defines
*/

# define BUFSIZE 1 << 6

size_t	ft_strlen(const char *str);

void	ft_append(char dst[BUFSIZE], const char *src);
void	ft_put_size(const size_t size, char buf[BUFSIZE]);
void	ft_put_addr(const void *addr, char buf[BUFSIZE]);

void	ft_print_total(const size_t total);
void	ft_print_chunk(const t_chunk_id *chunk);
void	ft_print_zone(const t_zone_id *zone, size_t *total);
void	ft_print_header(const void *addr, const enum e_type type);

void	ft_print(const char *str, const int fd);
void	ft_print_ln(char *str, const int fd);

void	ft_clrbuf(char *buf);

#endif
