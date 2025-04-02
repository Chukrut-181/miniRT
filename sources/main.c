/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/01 17:00:34 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void ft_testprinter(t_scene *scene)
{
	if (scene->ambient)
	{
		printf("Parsing Ambient:\n");
		printf("Ratio %f\n", scene->ambient->ratio);
		printf(" Color R = %f, G = %f, B = %f\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	}
	else
	{
		printf("No ambient detected\n");
	}
	if (scene->light)
	{
		printf("Parsing Light:\n");
		printf("Source X = %f, Y = %f, Z = %f\n", scene->light->source.x, scene->light->source.y, scene->light->source.z);
		printf("Intensity: %f\n", scene->light->intensity);
		printf("Color: R = %f, G = %f, B = %f\n", scene->light->color.r, scene->light->color.g, scene->light->color.b);
	}
	else
	{
		printf("No light detected\n");
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
