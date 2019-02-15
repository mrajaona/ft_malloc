#include "ft_malloc_print.h"

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

static void		ft_strcpy(char dst[BUFSIZE], const char *src, size_t offset)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = offset;
	if (!dst || !src)
		return ;
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

void			ft_append(char dst[BUFSIZE], const char *src)
{
	ft_strcpy(dst, src, ft_strlen(dst));
}

static size_t	ft_revnbr(size_t nbr)
{
	size_t	rev;

	rev = 0;
	while (nbr > 0)
	{
		rev = rev * 10 + (nbr % 10);
		nbr = nbr / 10;
	}
	return (rev);
}

void			ft_nbr(char buf[BUFSIZE], size_t n, unsigned b)
{
	size_t		i;
	unsigned	value;
	char		*base;

	if (b > 16)
		return ;
	if (n == 0)
	{
		ft_append(buf, "0");
		return ;
	}
	base = "0123456789ABCDEF";
	n = ft_revnbr(n);
	i = ft_strlen(buf);
	while (n > 0)
	{
		if (i == BUFSIZE)
		{
			ft_print(buf, STDOUT);
			ft_clrbuf(buf);
			i = 0;
		}
		value = n % b;
		buf[i] = base[value];
		n = n / b;
		i++;
	}
}

void			ft_print(const char *str, const int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

void			ft_print_ln(char *str, const int fd)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	str[len] = '\n';
	write(fd, str, len + 1);
}

void			ft_clrbuf(char *buf)
{
	size_t	i;

	i = 0;
	while (i < BUFSIZE)
	{
		buf[i] = 0;
		i++;
	}
}