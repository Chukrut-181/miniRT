/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/26 12:48:53 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_scene	*ft_init_scene(void)
{
	t_scene	*new_scene;

	new_scene = malloc(sizeof(t_scene));
	if (!new_scene)
		return (NULL);
	new_scene->camera = NULL;
	new_scene->world = malloc(sizeof(t_world));
	new_scene->world->ambient = NULL;
	new_scene->world->light = NULL;
	new_scene->mlx = NULL;
	new_scene->win = NULL;
	return (new_scene);
}

static void	init_mlx(t_scene *s)
{
	s->img.img_ptr = NULL;
	s->img.bits_per_pixel = 0;
	s->img.size_line = 0;
	s->img.endian = 0;
	s->mlx = mlx_init();
	s->img.img_ptr = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	s->img.data = mlx_get_data_addr(s->img.img_ptr, &s->img.bits_per_pixel,
			&s->img.size_line, &s->img.endian);
	s->win = mlx_new_window(s->mlx, WIDTH, HEIGHT, "miniRT");
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		ft_error_exit(NULL, "Error\nUsage: ./miniRT <arg1>", 1);
	scene = ft_init_scene();
	if (scene == NULL)
		ft_error_exit(NULL, "Error\nFailed to initialize scene", 1);
	get_scene(scene, argv[1]);
	init_mlx(scene);
	write(1, "Rendering\n", 10);
	render_scene(scene);
	write(1, "Finished!\n", 10);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img_ptr, 0, 0);
	mlx_key_hook(scene->win, key_hook, scene);
	mlx_hook(scene->win, 33, 1L << 17, close_hook, scene);
	mlx_loop(scene->mlx);
	ft_free_scene(scene);
	return (0);
}
