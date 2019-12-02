/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:51:13 by ahouel            #+#    #+#             */
/*   Updated: 2019/11/13 17:16:56 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	The reallocf() function is identical to the realloc() function, except
**	that it will free the passed pointer when the requested memory cannot be
**	allocated.  This is a FreeBSD specific API designed to ease the problems
**	with traditional coding styles for realloc causing memory leaks in
**	libraries.
*/

void	*reallocf(void *ptr, size_t size)
{
	void	*ret;

	ret = 0;
	if (!(ret = realloc(ptr, size)))
		free(ptr);
	return (ret);
}
