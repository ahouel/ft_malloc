/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:52:37 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/02 18:34:13 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Free the block given and fusion it with the next / prev one
**	in the linked list if they are also free
*/

static t_block	*defrag(t_block *b1, t_block *b2)
{
	t_block	*b3;

	b3 = b2->next;
	b1->size += sizeof(t_block) + b2->size;
	b1->next = b3;
	if (b3)
		b3->prev = b1;
	return (b1);
}

/*
**	Check if all blocks in an area are free
*/

static char		is_free(t_area *area)
{
	t_block	*block;

	block = area->blocks;
	while (block)
	{
		if (!block->free)
			return (0);
		block = block->next;
	}
	return (1);
}

/*
**	Delete an area from g_malloc_pages lists
*/

static void		delete_area(t_area *area)
{
	if (!area->prev && !area->next)
		return ;
	if (g_malloc_pages.tiny == area)
		g_malloc_pages.tiny = area->next;
	else if (g_malloc_pages.small == area)
		g_malloc_pages.small = area->next;
	else if (g_malloc_pages.large == area)
		g_malloc_pages.large = area->next;
	else if (area->prev)
		area->prev->next = area->next;
	if (area->next)
		area->next->prev = area->prev;
	if (munmap(area, area->size))
		return ;
}

/*
**	The free() function deallocates the memory allocation pointed
**	to by ptr. If ptr is a NULL pointer, no operation is performed.
*/

void			free(void *ptr)
{
	t_area	*area;
	t_block	*block;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	if (!(area = which_area(ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (!(block = is_block_valid(&area->blocks, ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	block->free = 1;
	if (block->prev && block->prev->free)
		block = defrag(block->prev, block);
	if (block->free && block->next && block->next->free)
		block = defrag(block, block->next);
	if (is_free(area))
		delete_area(area);
	pthread_mutex_unlock(&g_mutex);
}
