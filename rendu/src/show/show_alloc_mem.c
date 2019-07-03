#include "show_alloc_mem.h"

void    show_alloc_mem(void)
{
    write(1, "show_alloc_mem\n", 15);
    ft_printf("%s %i\n", "test", 1);
}