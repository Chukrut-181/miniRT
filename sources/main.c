/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/13 14:02:53 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void init_mlx(t_scene *s)
{
	s->img.img_ptr = NULL;
	s->img.bits_per_pixel = 0;
	s->img.size_line = 0;
	s->img.endian = 0;
	s->mlx = mlx_init();
	s->img.img_ptr = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	s->img.data = mlx_get_data_addr(s->img.img_ptr, &s->img.bits_per_pixel, &s->img.size_line, &s->img.endian);
	s->win = mlx_new_window(s->mlx, WIDTH, HEIGHT, "miniRT");
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>", 1);
	ft_get_scene(&scene, argv[1]);
	init_mlx(&scene);
	write(1, "Rendering..\n", 13);
	scene.camera->half_height = 0.242646822;
	scene.camera->half_width = 0.363970234266;
	scene.camera->pixel_size = 0.00040441137140;
	scene.camera->origin = ft_create_point(0, 0, -10);
	scene.camera->transform.data[0][0] = -1.0;
	scene.camera->transform.data[1][0] = 0;
	scene.camera->transform.data[2][0] = 0;
	scene.camera->transform.data[3][0] = 0;

	scene.camera->transform.data[0][1] = 0;
	scene.camera->transform.data[1][1] = 1.0;
	scene.camera->transform.data[2][1] = 0;
	scene.camera->transform.data[3][1] = 0;

	scene.camera->transform.data[0][2] = 0;
	scene.camera->transform.data[1][2] = 0;
	scene.camera->transform.data[2][2] = -1;
	scene.camera->transform.data[3][2] = 0;

	scene.camera->transform.data[0][3] = 0;
	scene.camera->transform.data[1][3] = 0;
	scene.camera->transform.data[2][3] = -10;
	scene.camera->transform.data[3][3] = 1;
	render_scene(&scene);
	write(1, "Finished\n", 9);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img.img_ptr, 0, 0);
	mlx_key_hook(scene.win, &key, &scene);
	mlx_loop(scene.mlx);
	ft_free_scene(&scene);
	return (0);
}
