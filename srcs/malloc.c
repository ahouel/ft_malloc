/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:51:55 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/02 18:06:06 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc_pages	g_malloc_pages = {0, 0, 0};
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
**	Takes the new desired size for a block and return the free block which's
**	size is the closest to the new one. Make it fit to lose the less memory.
*/

static t_block	*best_fit(t_area **lst_area, const size_t new_size)
{
	t_area	*area;
	t_block	*tmp;
	t_block	*best;

	best = 0;
	area = *lst_area;
	while (area)
	{
		tmp = area->blocks;
		while (tmp)
		{
			if (tmp->free)
			{
				if (tmp->size == new_size)
					return (tmp);
				if ((tmp->size > new_size) && \
						(!best || best->size > tmp->size))
					best = tmp;
			}
			tmp = tmp->next;
		}
		area = area->next;
	}
	return (best);
}

/*
**	Create a new area of the taken zone_size, set it's t_area header
**	and the first t_block header. Adds it to the top of the list taken.
*/

static t_area	*create_area(t_area **lst_area, const size_t zone_size)
{
	t_area	*area;
	t_area	*new;

	if ((new = mmap(0, zone_size, PROT, MAP, -1, 0)) == MAP_FAILED)
		return (0);
	ft_bzero(new, sizeof(t_area));
	new->size = zone_size;
	new->blocks = (void*)new + sizeof(t_area);
	ft_bzero(new->blocks, sizeof(t_block));
	new->blocks->size = zone_size - sizeof(t_block) - sizeof(t_area);
	area = *lst_area;
	if (!area)
		*lst_area = new;
	else
	{
		while (area->next)
			area = area->next;
		area->next = new;
		new->prev = area;
	}
	return (new);
}

/*
**	For a large malloc, mmap a new area and add it to the list.
**	Returns an array to the memory created.
*/

static void		*malloc_large(t_area **lst_area, const size_t size)
{
	t_area	*area;

	if (!(area = create_area(lst_area, size)))
		return (mmap_errors(size));
	return ((void*)area->blocks + sizeof(t_block));
}

/*
**	For a tiny or small malloc. Cross the existing areas already mmap'ed
**	to find a free block.
**	In case no free block was found, create a new area.
**	Returns an array to the memory found / created.
**	Second if condition is to split a block if it is big enough to contain
**	the new block and still have space for other ones.
*/

static void		*malloc_tiny_small(t_area **lst_area, const size_t zone_size, \
		const size_t size)
{
	t_area	*area;
	t_block	*block;
	t_block	*tmp;

	block = best_fit(lst_area, size);
	if (!block)
	{
		if (!(area = create_area(lst_area, zone_size)))
			return (mmap_errors(zone_size));
		block = area->blocks;
	}
	if (block->size - size >= sizeof(t_block))
	{
		tmp = block->next;
		block->next = (void*)block + sizeof(t_block) + size;
		ft_bzero(block->next, sizeof(t_block));
		block->next->free = 1;
		block->next->prev = block;
		block->next->size = block->size - size - sizeof(t_block);
		block->next->next = tmp;
		tmp ? tmp->prev = block->next : 0;
		block->size = size;
	}
	block->free = 0;
	return ((void*)block + sizeof(t_block));
}

/*
**	The malloc() function allocates size bytes of memory and returns
**	a pointer to the allocated memory.
*/

void			*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = 0;
	if (size < TINY_MAX + 1)
		ptr = malloc_tiny_small(&g_malloc_pages.tiny, \
				ft_align(ZONE_TINY, getpagesize()), ft_align(size, ALIGN));
	else if (size < SMALL_MAX + 1)
		ptr = malloc_tiny_small(&g_malloc_pages.small, \
				ft_align(ZONE_SMALL, getpagesize()), ft_align(size, ALIGN));
	else
		ptr = malloc_large(&g_malloc_pages.large, \
				ft_align(size + sizeof(t_area) + sizeof(t_block), \
					getpagesize()));
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
