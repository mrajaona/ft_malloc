#include "ft_malloc.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*srcs;
	size_t		i;

	if (src == NULL || dest == NULL)
		return (NULL);
	dst = dest;
	srcs = src;
	i = -1;
	while (++i < n)
		dst[i] = srcs[i];
	return ((void *)dst);
}