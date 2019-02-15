#include "ft_malloc_print.h"

/*
** appends a 1 for printing 0s correctly
*/
static size_t	ft_revnbr(size_t nbr, size_t base)
{
	size_t	rev;

	rev = 1;
	while (nbr > 0)
	{
		rev = rev * base + (nbr % base);
		nbr = nbr / base;
	}
	return (rev);
}

static void		ft_nbr(char buf[BUFSIZE], size_t n, unsigned b)
{
	size_t		i;
	unsigned	value;

	if (b > 16)
		return ;
	if (n == 0)
	{
		ft_append(buf, "0");
		return ;
	}
	n = ft_revnbr(n, b);
	i = ft_strlen(buf);
	while (n != 1)
	{
		if (i == BUFSIZE)
		{
			ft_print(buf, STDOUT);
			ft_clrbuf(buf);
			i = 0;
		}
		value = n % b;
		buf[i] = BASE_STR[value];
		n /= b;
		i++;
	}
}

void			ft_put_size(const size_t size, char buf[BUFSIZE])
{
	ft_nbr(buf, size, 10);
	ft_append(buf, UNIT);
}

void			ft_put_addr(const void *addr, char buf[BUFSIZE])
{
	ft_append(buf, HEAD_HEX);
	ft_nbr(buf, (size_t)addr, 16);
}