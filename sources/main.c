/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/27 15:22:25 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(int argc, char **argv)
{
	t_tuple *tuple = malloc(sizeof(t_tuple) * 1);

	tuple->x = 2;
	tuple->z = 2;
	tuple->y = 2;
	(void)argv;
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>", 1);
	else
		ft_minirt();
	return (0);
}
