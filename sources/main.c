/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/09 13:42:18 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* static void ft_4x4_printer(t_4x4 matrix)
{
    printf("4x4 Matrix:\n");
    int i = 0;
    while (i < 4)
    {
        printf("[ ");
        int j = 0;
        while (j < 4)
        {
            printf("%f ", matrix.data[i][j]);
            j++;
        }
        printf("]\n");
        i++;
    }
}

static void ft_testprinter(t_scene *scene)
{
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
	if (scene->world->light->source.w == 1)
	{
		printf("Parsing Light:\n");
		printf("Source coords: X = %.4f, Y = %.4f, Z = %.4f\n", scene->world->light->source.x, scene->world->light->source.y, scene->world->light->source.z);
		printf("Color ratios:  R = %.4f, G = %.4f, B = %.4f\n", scene->world->light->l_color.r, scene->world->light->l_color.g, scene->world->light->l_color.b);
	}
	else
	{
		printf("No light detected\n");
	}
	if (scene->camera)
	{
		printf("Camera detected OK but not yet parsed properly\n");
		printf("FOV: %.4f\n", scene->camera->field_of_view);
	}
	else
		printf("No camera detected\n");
	int sphere_count = 0;
	int plane_count = 0;
	if (!scene->world->objects)
		printf("No objects detected\n");
	else
	{
		printf("Parsing object list:\n");
		t_list *current = scene->world->objects;
		while (current) 
		{
			t_shape shape = *(t_shape *)(current->content);
			if (shape.type == SPHERE)
			{
				sphere_count++;
				printf("Sphere detected with associated transformation matrix:\n");
				ft_4x4_printer(shape.transform_matrix);
			}
			else if (shape.type == PLANE)
			{
				plane_count++;
				printf("Plane detected with associated transformation matrix:\n");
				ft_4x4_printer(shape.transform_matrix);
			}
			current = current->next;
		}
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
	ft_create_scene(&scene, argv[1]);
//	ft_testprinter(&scene);
	init_mlx(&scene);
	render_scene(&scene, *scene.camera, *scene.world);
	mlx_image_to_window(scene.mlx, scene.image, 0, 0);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	return (0);
}
