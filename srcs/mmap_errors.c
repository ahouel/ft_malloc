/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:00:37 by ahouel            #+#    #+#             */
/*   Updated: 2019/08/13 12:57:55 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	Called if a mmap failed allocation <size> memory
**	Print an error on the error filedescriptor and returns null
*/

void	*mmap_errors(const size_t size)
{
	ft_putstr_fd("Mmap failed allocating ", 2);
	ft_putnbr_fd((int)size, 2);
	ft_putstr_fd(" memory.\n", 2);
	return (0);
}
