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

/*
** more defines
*/

# define BUFSIZE 1024

void	ft_append(char *dst, const char *src);

void	ft_print(const char *str, const int fd);
void	ft_print_ln(char *str, const int fd);

void	ft_clrbuf(char *buf);

#endif
