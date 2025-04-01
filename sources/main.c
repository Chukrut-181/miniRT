/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/01 15:37:12 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void ft_testprinter(t_scene *scene)
{
	if (scene->ambient)
	{
		printf("Ratio %f, Color R = %f, G = %f, B = %f\n", scene->ambient->ratio, scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	}
	else
	{
		printf("No ambient detected\n");
	}
}

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
	ft_testprinter(&scene);	
	//ft_minirt();
	return (0);
}
