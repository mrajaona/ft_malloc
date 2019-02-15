#include "ft_malloc_print.h"

void	ft_print(const char *str, const int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

void	ft_print_ln(char *str, const int fd)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	str[len] = '\n';
	write(fd, str, len + 1);
}