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

static t_scene *init_scene(void)
{
    t_scene *scene;

    // Asignar memoria para la estructura principal
    scene = (t_scene *)malloc(sizeof(t_scene));
    if (!scene)
        return (NULL);

    // Inicializar valores básicos
    scene->mlx = NULL;
    scene->image = NULL;

    // Inicializar cámara
    scene->camera = (t_camera *)malloc(sizeof(t_camera));
    if (!scene->camera)
    {
        free(scene);
        return (NULL);
    }
    scene->camera->hsize = 0.0;
    scene->camera->vsize = 0.0;
    scene->camera->field_of_view = 0.0;
    scene->camera->pixel_size = 0.0;
    scene->camera->half_width = 0.0;
    scene->camera->half_height = 0.0;
    scene->camera->init = 0;
    scene->camera->origin = (t_tuple){0.0, 0.0, 0.0, 1};
    // Inicializar matriz de transformación con matriz identidad
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scene->camera->transform.data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Inicializar ambiente
    scene->ambient = (t_ambient *)malloc(sizeof(t_ambient));
    if (!scene->ambient)
    {
        free(scene->camera);
        free(scene);
        return (NULL);
    }
    scene->ambient->a_color = (t_color){1.0, 1.0, 1.0};
    scene->ambient->ratio = 0.1;

    // Inicializar luz
    scene->light = (t_light *)malloc(sizeof(t_light));
    if (!scene->light)
    {
        free(scene->ambient);
        free(scene->camera);
        free(scene);
        return (NULL);
    }
    scene->light->source = (t_tuple){0.0, 0.0, 0.0, 1};
    scene->light->l_color = (t_color){1.0, 1.0, 1.0};
    scene->light->intensity = 1.0;

    // Inicializar mundo
    scene->world = (t_world *)malloc(sizeof(t_world));
    if (!scene->world)
    {
        free(scene->light);
        free(scene->ambient);
        free(scene->camera);
        free(scene);
        return (NULL);
    }
    scene->world->objects = NULL;  // Lista vacía de objetos
    scene->world->shape_count = 0;

    return (scene);
}

static void free_scene(t_scene *scene)
{
    if (!scene)
        return;

    // Liberar la imagen MLX si existe
    if (scene->image)
    {
        // No liberamos la imagen aquí, ya que MLX42 tiene su propia función para eso
        // mlx_delete_image(scene->mlx, scene->image);
    }

    // Liberar el mundo y sus objetos
    if (scene->world)
    {
        // Liberar la lista de objetos si existe
        if (scene->world->objects)
        {
            // Aquí deberías usar una función para liberar cada nodo de la lista
            // y los objetos contenidos en ella
            // ft_lstclear(&scene->world->objects, free_object);
        }
        free(scene->world);
    }

    // Liberar otros componentes
    if (scene->light)
        free(scene->light);
    if (scene->ambient)
        free(scene->ambient);
    if (scene->camera)
        free(scene->camera);

    // Finalmente, liberar la estructura principal
    free(scene);
}

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
	t_scene	*scene;
	
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>", 1);
	scene = init_scene();
	ft_get_scene(scene, argv[1]);
//	ft_testprinter(&scene);
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
