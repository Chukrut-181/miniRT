/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/07 11:37:56 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* static void ft_testprinter(t_scene *scene)
{
//	t_sphere	*aux;
	
	if (scene->ambient)
	{
		printf("Parsing Ambient:\n");
		printf("Ratio %.4f\n", scene->ambient->ratio);
		printf(" Color R = %.4f, G = %.4f, B = %.4f\n", scene->ambient->a_color.r, scene->ambient->a_color.g, scene->ambient->a_color.b);
	}
	else
	{
		printf("No ambient detected\n");
	}
	if (scene->light)
	{
		printf("Parsing Light:\n");
		printf("Source X = %.4f, Y = %.4f, Z = %.4f\n", scene->light->source.x, scene->light->source.y, scene->light->source.z);
		//printf("Intensity: %.4f\n", scene->light->intensity.x);
		printf("Color: R = %.4f, G = %.4f, B = %.4f\n", scene->light->l_color.r, scene->light->l_color.g, scene->light->l_color.b);
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
	if (!scene->objects)
		printf("No objects detected\n");
	else
		printf("Parsing object list:\n");
	// Contar objetos por tipo
	int sphere_count = 0;
	int plane_count = 0;
	t_list *current = scene->objects;
	while (current) {
		t_type obj_type = *(t_type *)(current->content);
		if (obj_type == SPHERE) sphere_count++;
		else if (obj_type == PLANE) plane_count++;
		current = current->next;
	}
	printf("Objects in scene: %d spheres, %d planes\n", sphere_count, plane_count);
} */

static	void	init_mlx(t_scene *s)
{
	s->mlx = mlx_init(2400, 1800, "miniRT", NULL);
	if (!s->mlx)
		exit(1);
	s->image = mlx_new_image(s->mlx, 2400, 1800);
	if (!s->image || (mlx_image_to_window(s->mlx, s->image, 0, 0) < 0))
		exit(1);
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
	ft_get_scene(&scene, argv[1]);
//	ft_testprinter(&scene);
	init_mlx(&scene);
	render_scene(&scene, *scene.camera, *scene.world);
	mlx_image_to_window(scene.mlx, scene.image, 0, 0);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	return (0);
}
