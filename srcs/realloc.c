/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:53:11 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/02 18:34:12 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Return the block for which the memory allocated is pointed by ptr.
*/

static t_block	*get_block(void *ptr)
{
	t_area	*area;
	t_block	*block;

	if (!(area = which_area(ptr)))
		return (0);
	if (!(block = is_block_valid(&area->blocks, ptr)))
		return (0);
	return (block);
}

/*
**	The realloc() function tries to change the size of the allocation
**	pointed to by ptr to size, and returns ptr.  If there is not enough room
**	to enlarge the memory allocation pointed to by ptr, realloc() creates a
**	new allocation, copies as much of the old data pointed to by ptr as will
**	fit to the new allocation, frees the old allocation, and returns a
**	pointer to the allocated memory.  If ptr is NULL, realloc() is identical
**	to a call to malloc() for size bytes.  If size is zero and ptr is not
**	NULL, a new, minimum sized object is allocated and the original object
**	is freed.  When extending a region allocated with calloc(), realloc()
**	does not guarantee that the additional memory is also zero-filled.
*/

void			*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*ret;

	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_mutex);
	if (!(block = get_block(ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (0);
	}
	if (size <= block->size)
	{
		pthread_mutex_unlock(&g_mutex);
		if (!size)
		{
			free(ptr);
			ptr = malloc(size);
		}
		return (ptr);
	}
	pthread_mutex_unlock(&g_mutex);
	if (!(ret = malloc(size)))
		return (ptr);
	pthread_mutex_lock(&g_mutex);
	ft_memcpy(ret, ptr, block->size);
	pthread_mutex_unlock(&g_mutex);
	free(ptr);
	return (ret);
}
