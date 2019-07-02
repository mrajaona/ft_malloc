#include "merge.h"

t_elem_info	*merge(t_elem_info *lhs, t_elem_info *rhs)
{
	if (!lhs || !rhs)
		return ;
	lhs->size = lhs->size + sizeof(t_elem_info) + rhs->size;
    if (rhs->next)
        rhs->next->prev = lhs;
	lhs->next = rhs->next;        
	return (lhs);
}