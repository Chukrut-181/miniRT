/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/04 10:56:48 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void ft_testprinter(t_scene *scene)
{
	if (scene->ambient)
	{
		printf("Parsing Ambient:\n");
		printf("Ratio %.4f\n", scene->ambient->ratio);
		printf(" Color R = %.4f, G = %.4f, B = %.4f\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	}
	else
	{
		printf("No ambient detected\n");
	}
	if (scene->light)
	{
		printf("Parsing Light:\n");
		printf("Source X = %.4f, Y = %.4f, Z = %.4f\n", scene->light->source.x, scene->light->source.y, scene->light->source.z);
		printf("Intensity: %.4f\n", scene->light->intensity);
		printf("Color: R = %.4f, G = %.4f, B = %.4f\n", scene->light->color.r, scene->light->color.g, scene->light->color.b);
	}
	else
	{
		printf("No light detected\n");
	}
	if (scene->camera)
	{
		printf("Parsing Camera:\n");
		printf("Viewpoint X = %.4f, Y = %.4f, Z = %.4f\n", scene->camera->viewpoint.x, scene->camera->viewpoint.y, scene->camera->viewpoint.z);
		printf("Orientation X = %.4f, Y = %.4f, Z = %.4f\n", scene->camera->v_orientation.x, scene->camera->v_orientation.y, scene->camera->v_orientation.z);
		printf("FOV: %.4f\n", scene->camera->field_of_view);
	}
	else
		printf("No camera detected\n");
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>", 1);
	scene.mlx = NULL;
	scene.image = NULL;
	scene.camera = NULL;
	scene.ambient = NULL;
	scene.light = NULL;
	scene.objects = NULL;
	ft_get_scene(&scene, argv[1]);
	ft_testprinter(&scene);	
	//ft_minirt();
	return (0);
}
