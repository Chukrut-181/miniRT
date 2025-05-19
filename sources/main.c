/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/19 11:46:19 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
static void ft_4x4_checkprinter(t_4x4 matrix)
{
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        printf("[");
        j = 0;
        while (j < 4)
        {
            printf("%8.3f ", matrix.data[i][j]);
            j++;
        }
        printf("]\n");
        i++;
    }
}

static void ft_parsingcheckerprinter(t_scene *scene)
{
	printf("\n*** SCENE PARSING CHECK ***\n\n");
	if (scene->ambient)
	{
		printf("AMBIENT LIGHT\n");
		printf("Ratio: %.4f\n", scene->ambient->ratio);
		printf("Color RGB[0-1]: (%.4f, %.4f, %.4f)\n", scene->ambient->a_color.r, scene->ambient->a_color.g, scene->ambient->a_color.b);
		printf("\n");
	}
	if (scene->camera)
	{
		printf("CAMERA\n");
		printf("Origin: (%.4f, %.4f, %.4f)\n", scene->camera->origin.x, scene->camera->origin.y, scene->camera->origin.z);
		printf("Direction: (%.4f, %.4f, %.4f)\n", scene->camera->transform.data[2][0], scene->camera->transform.data[2][1], scene->camera->transform.data[2][2]);
		printf("Field of view: %f\n", scene->camera->field_of_view);
		printf("Associated Transformation Matrix:\n");
		ft_4x4_checkprinter(scene->camera->transform);
		printf("\n");

	}
	if (scene->world)
	{
		if (scene->world->light)
		{
			printf("WORLD\n");
			printf("Light:\n");
			printf("Source XYZ: (%.4f, %.4f, %.4f)\n", scene->world->light->source.x, scene->world->light->source.y, scene->world->light->source.z);
			printf("Color RGB[0-1]: (%.4f, %.4f, %.4f)\n", scene->world->light->l_color.r, scene->world->light->l_color.g, scene->world->light->l_color.b);
			printf("Intensity: %.4f\n", scene->world->light->intensity);
			printf("\n");
		}
		if (scene->world->objects)
		{
			printf("OBJECTS detected in world:\n");
			while (scene->world->objects)
			{
				t_shape *shape = scene->world->objects->content;
				if (shape->type == SPHERE)
				{
					printf("Sphere\n");
					printf("Associated Transformation Matrix:\n");
					ft_4x4_checkprinter(shape->transform_matrix);
					printf("\n");
				}
				else if (shape->type == PLANE)
				{
					printf("Plane\n");
					printf("Associated Transformation Matrix:\n");
					ft_4x4_checkprinter(shape->transform_matrix);
					printf("\n");
				}
				else
					printf("Unknown shape detected!\n");
				scene->world->objects = scene->world->objects->next;
			}
		}
		else
			printf("No objects in the world.\n");
	}
} */

static t_scene *ft_init_scene(void)
{
	t_scene *new_scene = malloc(sizeof(t_scene));
	if (!new_scene)
		return (NULL);
	new_scene->ambient = NULL;
	new_scene->camera = NULL;
	new_scene->world = malloc(sizeof(t_world));
	new_scene->mlx = NULL;
	new_scene->win = NULL;
	return (new_scene);
}

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
	t_scene	*scene;
	
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>", 1);
	scene = ft_init_scene();
	if (scene == NULL)
		ft_error_exit("Error\nFailed to initialize scene", 1);
	ft_get_scene(scene, argv[1]);
//	ft_parsingcheckerprinter(scene);
	init_mlx(scene);
	write(1, "Rendering..\n", 13); 
	render_scene(scene);
    write(1, "Finished\n", 9);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img_ptr, 0, 0);
	mlx_key_hook(scene->win, key_hook, scene);
	mlx_hook(scene->win, 33, 1L << 17, close_hook, scene);
	mlx_loop(scene->mlx);
	write(1, "olakease\n", 13);
	ft_free_scene(scene);
	return (0);
}
