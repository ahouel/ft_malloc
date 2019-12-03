/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:36:59 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/03 18:11:50 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	STUPIDE NORMINETTE
**	Remplace defines...
*/

size_t	zone_tiny(void)
{
	return ((TINY_MAX + sizeof(t_block)) * MULT + sizeof(t_area));
}
