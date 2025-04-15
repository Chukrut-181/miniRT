/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/10 15:57:03 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	ft_initialize_mlx(t_scene *scene)
{
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!scene->mlx)
	{
		ft_free_scene(scene);
		ft_error_exit("Error\nFailed to initialize MLX", 1);
	}
	scene->image = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!scene->image)
	{
		ft_free_scene(scene);
		mlx_terminate(scene->mlx);
		ft_error_exit("Error\nFailed to initialize image", 1);
	}
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>\n", 1);
	scene.mlx = NULL;
	scene.image = NULL;
	scene.camera = NULL;
	scene.ambient = NULL;
	scene.light = NULL;
	scene.objects = NULL;
	ft_create_scene(&scene, argv[1]);
	ft_initialize_mlx(&scene);
	ft_minirt(&scene);
	//ft_testprinter(&scene);
	return (0);
}
