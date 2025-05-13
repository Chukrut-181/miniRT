/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/12 17:01:15 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static	void	init_mlx(t_scene *s)
{
	s->mlx = mlx_init(2400, 1800, "miniRT", NULL);
	if (!s->mlx)
		exit(1);
	s->image = mlx_new_image(s->mlx, 2400, 1800);
	if (!s->image)
		exit(1);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>", 1);
	ft_get_scene(scene, argv[1]);
	init_mlx(scene);
    write(1, "Rendering..\n", 13); 
	render_scene(scene);
    write(1, "Finished\n", 9);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);
	free_scene(scene);
	return (0);
}
