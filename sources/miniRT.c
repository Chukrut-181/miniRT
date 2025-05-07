/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:09:31 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/07 14:24:22 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../include/minirt.h"

static void	ft_print_matrix(t_4x4 matrix)
{
    int	i;
    int	j;

	i = 0;
    while (i < 4)
    {
		j = 0;
		while (j < 4)
		{
			printf("%10.4f ", matrix.data[i][j]);
			j++;
		}
        printf("\n");
		i++;
    }
}

static void ft_testprinter(t_scene *scene)
{
	t_list		*temp;
	t_object	*obj;

	if (scene->image)
		printf("Image detected OK\n");
	else
		printf("No image detected\n");
	if (scene->mlx)
		printf("MLX detected OK\n");
	else
		printf("No MLX detected\n");
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
	if (scene->objects)
	{
		temp = scene->objects;
		printf("Some objects detected:\n");
		while (temp)
		{
			if (temp->content)
			{
				obj = (t_object *)temp->content;
				if (obj->type == SPHERE)
				{
					printf("Sphere detected\n");
					ft_print_matrix(obj->transform);
				}
				else if (obj->type == PLANE)
					printf("Plane detected\n");
				else if (obj->type == CYLINDER)
					printf("Cylinder detected\n");
				else if (obj->type == CUBE)
					printf("Cube detected\n");
				else
					printf("Unknown object type\n");
			}
			temp = temp->next;
		}
	}
	else
		printf("No objects detected:\n");
}

int ft_minirt(t_scene *scene)
{
	ft_testprinter(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	mlx_key_hook(scene->mlx, ft_handle_key, scene->mlx);
	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);
	return (0);
}

 */