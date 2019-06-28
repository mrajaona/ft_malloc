#include "merge.h"

t_elem_info	*merge(t_elem_info *lhs, t_elem_info *rhs)
{
	lhs->size = lhs->size + sizeof(t_elem_info) + rhs->size;
	lhs->next = rhs->next;
	return (lhs);
}