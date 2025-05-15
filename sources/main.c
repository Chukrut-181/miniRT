/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/15 12:55:31 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
		printf("Pixel size: %f\n", scene->camera->pixel_size);
		printf("Half width: %f\n", scene->camera->half_width);
		printf("Half height: %f\n", scene->camera->half_height);
		printf("Horizontal size: %.4f\n", scene->camera->hsize);
		printf("Vertical size: %.4f\n", scene->camera->vsize);	
		printf("Associated Transformation Matrix:\n");
		ft_4x4_checkprinter(scene->camera->transform);
		printf("\n");

	}
	if (scene->world)
	{
		if (scene->world->light)
		{
			printf("WORLD\n\n");
			printf("LIGHT in WORLD:\n");
			printf("Source XYZ: (%.2f, %.2f, %.2f)\n", scene->world->light->source.x, scene->world->light->source.y, scene->world->light->source.z);
			printf("Color RGB[0-1]: (%.4f, %.4f, %.4f)\n", scene->world->light->l_color.r, scene->world->light->l_color.g, scene->world->light->l_color.b);
			printf("Intensity: %.2f\n", scene->world->light->intensity);
			printf("\n");
		}
		if (scene->world->objects)
		{
			printf("OBJECTS present in WORLD:\n");
			while (scene->world->objects)
			{
				t_shape *shape = scene->world->objects->content;
				if (shape->type == SPHERE)
				{
					printf("Sphere\n");
					printf("Colors RGB[0-1]: %.3f, %.3f, %.3f\n", shape->material.color.r, shape->material.color.g, shape->material.color.b);
					printf("Associated Transformation Matrix:\n");
					ft_4x4_checkprinter(shape->transform_matrix);
					printf("\n");
				}
				else if (shape->type == PLANE)
				{
					printf("Plane\n");
					printf("Colors RGB[0-1]: %.3f, %.3f, %.3f\n", shape->material.color.r, shape->material.color.g, shape->material.color.b);
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
}
static t_scene *ft_init_scene(void)
{
	t_scene *new_scene = ft_calloc(1, sizeof(t_scene));
	new_scene->ambient = ft_calloc(1, sizeof(t_ambient));
	new_scene->camera = ft_calloc(1, sizeof(t_camera));
	new_scene->world = ft_calloc(1, sizeof(t_world));
	new_scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	new_scene->image = mlx_new_image(new_scene->mlx, WIDTH, HEIGHT);
	if (!new_scene || !new_scene->ambient || !new_scene->camera || !new_scene->world || !new_scene->mlx || !new_scene->image)
		ft_error_exit(new_scene, "Error\nFailed to initialize scene", 1);
	return (new_scene);
}


int	main(int argc, char **argv)
{
	t_scene	*scene;
	
	if (argc != 2)
		ft_error_exit(NULL, "Error\nUsage: ./miniRT <arg1>", 1);
	scene = ft_init_scene();
	ft_get_scene(scene, argv[1]);
	ft_parsingcheckerprinter(scene);
	//write(1, "Rendering..\n", 13); 
	//render_scene(scene);
    //write(1, "Finished\n", 9);
	//mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	//mlx_loop(scene->mlx);
	//mlx_terminate(scene->mlx);
	ft_free_scene(scene);
	return (0);
}
