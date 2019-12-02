/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_area.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:05:31 by ahouel            #+#    #+#             */
/*   Updated: 2019/11/13 17:06:59 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Takes an array and returns the t_area in which it is.
*/

t_area	*which_area(void *ptr)
{
	t_area	*area;

	area = g_malloc_pages.tiny;
	while (area)
	{
		if (ptr > (void*)area && ptr < (void*)area + area->size)
			return (area);
		area = area->next;
	}
	area = g_malloc_pages.small;
	while (area)
	{
		if (ptr > (void*)area && ptr < (void*)area + area->size)
			return (area);
		area = area->next;
	}
	area = g_malloc_pages.large;
	while (area)
	{
		if (ptr > (void*)area && ptr < (void*)area + area->size)
			return (area);
		area = area->next;
	}
	return (0);
}
