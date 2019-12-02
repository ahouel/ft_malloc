/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:20:18 by ahouel            #+#    #+#             */
/*   Updated: 2019/11/13 17:17:41 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	The calloc() function contiguously allocates enough space for count
**	objects that are size bytes of memory each and returns a pointer to
**	the allocated memory.  The allocated memory is filled with bytes of
**	value zero.
*/

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	if ((ptr = malloc(count * size)))
		ft_bzero(ptr, count * size);
	return (ptr);
}
