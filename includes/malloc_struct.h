/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:55:20 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/03 18:28:15 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_STRUCT_H
# define MALLOC_STRUCT_H

# define MULT				100
# define TINY_MAX			1024
# define SMALL_MAX			4096

# define ALIGN				16

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
