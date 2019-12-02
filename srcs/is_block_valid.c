/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_block_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:50:18 by ahouel            #+#    #+#             */
/*   Updated: 2019/11/07 18:48:25 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Takes an array and the list of blocks in which it is supposed to be
**	Returns
*/

t_block	*is_block_valid(t_block **block_lst, void *ptr)
{
	t_block	*block;

	block = *block_lst;
	while (block && (size_t)block < (size_t)ptr)
	{
		if ((size_t)block + sizeof(t_block) == (size_t)ptr)
			return (block);
		block = block->next;
	}
	return (0);
}
