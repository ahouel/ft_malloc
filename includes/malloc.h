/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:54:04 by ahouel            #+#    #+#             */
/*   Updated: 2019/11/13 17:41:29 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <pthread.h>

# include "libft.h"
# include "malloc_struct.h"

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*reallocf(void *ptr, size_t size);
void	*calloc(size_t count, size_t size);
t_area	*which_area(void *ptr);
t_block	*is_block_valid(t_block **block_lst, void *ptr);
void	*mmap_errors(const size_t size);
void	show_alloc_mem(void);
size_t	ft_align(size_t size, size_t align);

#endif
