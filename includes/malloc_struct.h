/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:55:20 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/02 18:05:20 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_STRUCT_H
# define MALLOC_STRUCT_H

# define MULT				100
# define TINY_MAX			(size_t)1024
# define SMALL_MAX			(size_t)4096
# define TINY_MULT			(TINY_MAX + sizeof(t_block)) * MULT
# define SMALL_MULT			(SMALL_MAX + sizeof(t_block)) * MULT
# define ZONE_TINY			(size_t)TINY_MULT + sizeof(t_area)
# define ZONE_SMALL			(size_t)SMALL_MULT + sizeof(t_area)

# define ALIGN				16

# define PROT				PROT_READ | PROT_WRITE
# define MAP				MAP_ANON | MAP_PRIVATE

# define MEM_COLUMNS		20
# define MEM_SHORT			1

/*
**	Structure heading each block of memory
*/

typedef struct			s_block {
	char			free;
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
}						t_block;

/*
**	Structure heading each area of memory blocks
*/

typedef struct			s_area {
	t_block			*blocks;
	struct s_area	*prev;
	struct s_area	*next;
	size_t			size;
}						t_area;

typedef	struct			s_malloc_pages {
	t_area	*tiny;
	t_area	*small;
	t_area	*large;
}						t_malloc_pages;

/*
**	Globals for malloc pages and multithread
*/

extern t_malloc_pages	g_malloc_pages;
extern pthread_mutex_t	g_mutex;

#endif
