/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:08:39 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/03 18:13:48 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	STUPIDE NORMINETTE
**	Remplace defines...
*/

size_t	zone_small(void)
{
	return ((SMALL_MAX + sizeof(t_block)) * MULT + sizeof(t_area));
}
