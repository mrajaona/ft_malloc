#include "ft_malloc_print.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_append(char dst[BUFSIZE], const char *src)
{
	size_t	i;
	size_t	j;

	if (!dst || !src)
		return ;
	i = 0;
	j = ft_strlen(dst);
	while (src[i])
	{
		if (j == BUFSIZE)
		{
			ft_print(dst, STDOUT);
			ft_clrbuf(dst);
			j = 0;
		}
		dst[j] = src[i];
		i++;
		j++;
	}
}

void	ft_clrbuf(char *buf)
{
	size_t	i;

	i = 0;
	while (i < BUFSIZE)
	{
		buf[i] = 0;
		i++;
	}
}