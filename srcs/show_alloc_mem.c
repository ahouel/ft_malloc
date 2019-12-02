/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:03:49 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/02 17:21:22 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Take an array to the memory of a block and it's size
**	Print each byte of it in hexadecimal form
*/

static void	show_mem(const void *mem, size_t size)
{
	unsigned char	*ptr;
	int				column;

	column = 0;
	ptr = (unsigned char*)mem;
	while (size)
	{
		if (*ptr)
			ft_putnbr_base((size_t)(*ptr), 16);
		else
			ft_putstr("0x00");
		ptr++;
		size--;
		column++;
		if (!(column % MEM_COLUMNS) && size)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

/*
**	For each block in the taken list, show it's position,
**	size, and if it's free the memory inside
*/

static void	show_blocks(t_block **list)
{
	t_block	*block;

	block = *list;
	while (block)
	{
		ft_putstr(COLOR_CYAN);
		ft_putstr("Block : ");
		ft_putnbr_base((size_t)block, 16);
		ft_putstr(COLOR_NORMAL);
		ft_putstr("\tSize : ");
		ft_putnbr_base(block->size, 10);
		ft_putstr("\tIs free : ");
		ft_putstr((block->free ? "YES" : "NO"));
		if (!block->free && !MEM_SHORT)
		{
			ft_putstr("\nMemory :\n");
			show_mem((void*)block + sizeof(t_block), block->size);
		}
		block = block->next;
		ft_putchar('\n');
	}
}

/*
**	For each area in the taken list, show it's position,
**	and the list of blocks inside it
*/

static void	show_area(t_area **lst_area)
{
	t_area	*area;

	area = *lst_area;
	while (area)
	{
		ft_putstr(COLOR_YELLOW);
		ft_putstr("Area : ");
		ft_putnbr_base((size_t)(area), 16);
		ft_putstr(COLOR_NORMAL);
		ft_putchar('\n');
		show_blocks(&area->blocks);
		area = area->next;
	}
}

/*
**	Function to show the allocate memory from malloc
*/

void		show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	ft_putstr(COLOR_MAGENTA);
	ft_putstr("Memory allocated :\n");
	ft_putstr(COLOR_RED);
	ft_putstr("Tiny pages :\n");
	ft_putstr(COLOR_NORMAL);
	show_area(&g_malloc_pages.tiny);
	ft_putstr(COLOR_RED);
	ft_putstr("Small pages :\n");
	ft_putstr(COLOR_NORMAL);
	show_area(&g_malloc_pages.small);
	ft_putstr(COLOR_RED);
	ft_putstr("Large pages : \n");
	ft_putstr(COLOR_NORMAL);
	show_area(&g_malloc_pages.large);
	pthread_mutex_unlock(&g_mutex);
}
