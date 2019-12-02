/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:55:34 by ahouel            #+#    #+#             */
/*   Updated: 2019/12/02 18:31:53 by ahouel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(int ac, char **av)
{
	char	*str;

	ft_putstr(COLOR_MAGENTA);
	ft_putstr("Test started ! \n");
	ft_putstr(COLOR_NORMAL);
	if (!(str = malloc(42)))
		return (-1);
	free(str);
	ft_putstr(COLOR_MAGENTA);
	ft_putstr("Test ended ! \n");
	ft_putstr(COLOR_NORMAL);
	return (0);
}
