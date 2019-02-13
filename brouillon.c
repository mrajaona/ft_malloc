// todo : threads

void		free(void *ptr);
{
	if (!large)
	{
		set free
		merge consecutive free blocks in list
		check empty list
			munmap	
	}
	else // large
	{
		remove from lst
		munmap
	}
}

void		*malloc(size_t size);
{
	check type of allocation
	if (!large)
	{
		check available space in existing zones
		if (enough space)
		{
			put in zone
		}
		else
		{
			create zone
			put in new zone
		}
	}
	else // large
	{
		add to g_lst_large
	}
	return addr
}

void		*realloc(void *ptr, size_t size);
{
	if (!large)
	{
		check if next block is free
		if free
		{
			check if enough size
			if enough
			{
				edit block size
				edit free block position and size
					delete if size is 0
					update lst
				retrun old
			}
			else
			{
				return (realloc_no_space)
			}
		}
		else // !free
		{
			return (realloc_no_space)
		}
	}
	else // large
	{
		return (realloc_no_space)
	}
}

realloc_no_space
{
	malloc new
	copy old to new
	replace old with new in lst
	free old
	return new
}
