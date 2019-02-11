#include "ft_malloc.h"

static void	*ft_realloc_large(void *src, size_t size)
{
	void			*ptr;
	t_identifier	*id;
	size_t			aligned;

	/*
	if (too small)
	{
	*/
		aligned = align(size);
		ptr = malloc(size);
		ft_memcpy(ptr, src,
			((t_identifier *)(src - sizeof(t_identifier)))->size);
		id = (t_identifier *)(ptr - sizeof(t_identifier));
		id->type = LARGE;
		id->size = aligned - sizeof(t_identifier);
		id->prev = NULL;
		id->next = NULL;
		return (ptr);
	/*
	}
	else
		return (ptr);
	*/

}

void	*realloc(void *ptr, size_t size)
{
	write(1, "realloc\n", 8);
	if (ptr == NULL)
		return (malloc(size));
	else //if (size > SMALL_MAX)
		return (ft_realloc_large(ptr, size));
}