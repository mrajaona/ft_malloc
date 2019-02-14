#include "ft_malloc_print.h"

/*
void	ft_print_hex(const size_t n)
{
	;
}

void	ft_print_dec(const size_t n)
{
	;
}
*/

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return ;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

void		ft_append(char *dst, const char *src)
{
	ft_strcpy(dst + ft_strlen(dst), src);
}


void		ft_print(const char *str, const int fd)
{
	write(fd, str, ft_strlen(str));
}

void		ft_print_ln(char *str, const int fd)
{
	size_t	len;

	len = ft_strlen(str);
	str[len] = '\n';
	write(fd, str, len + 1);
}

void		ft_clrbuf(char *buf)
{
	size_t	i;

	i = 0;
	while (i < BUFSIZE)
	{
		buf[i] = 0;
		i++;
	}
}