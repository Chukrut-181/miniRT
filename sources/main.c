/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/01 13:28:37 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(int argc, char **argv)
{
	t_scene	scene;
	
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>", 1);
	scene.mlx = NULL;
	scene.image = NULL;
	scene.ambient = NULL;
	scene.light = NULL;
	scene.objects = NULL;
	ft_get_scene(&scene, argv[1]);
	ft_minirt();
	
	return (0);
}
