#include <stdio.h>
#include <stdbool.h>

// #include "ft_malloc.h"

enum	e_type
{
	TINY,
	SMALL,
	LARGE
};

typedef struct	s_block_id
{
	enum e_type			type;
	void				*addr;
	size_t				size;
	bool				isfree;
	struct s_block_id	*prev;
	struct s_block_id	*next;
}				t_chunk_id;

typedef struct	s_zone_id
{
	size_t				size;
	struct s_zone_id	*prev;
	struct s_zone_id	*next;
}				t_zone_id;

typedef struct	s_empty
{
}				t_empty;

typedef struct	s_test
{
	bool	p;
	long 	l;
}				t_test;

int	main(int ac, char **av)
{
	(void)ac; (void)av;
	printf("%ld %ld %ld %ld\n", sizeof(enum e_type), sizeof(t_chunk_id), sizeof(t_zone_id), sizeof(bool));
	printf("%ld %ld\n", sizeof(t_empty), sizeof(t_test));
	return (0);
}