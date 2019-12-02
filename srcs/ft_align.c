/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_align.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:04:43 by ahouel            #+#    #+#             */
/*   Updated: 2019/10/25 17:35:18 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	ft_align(size_t size, size_t align)
{
	if (size < align + 1)
		return (align);
	if (!(size % align))
		return (size);
	return (size + (align - (size % align)));
}
