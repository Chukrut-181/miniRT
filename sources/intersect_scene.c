/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:21:35 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/14 16:06:49 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_list	*ft_intersect_objects(t_ray ray, t_list *objects, t_list *xs_list)
{
    t_list		*current;
    t_sphere	*sphere;
    t_plane		*plane;

    current = objects;
    while (current)
    {
        if (!current->content)
        {
            current = current->next;
            continue;
        }
        if (((t_sphere *)current->content)->type == SPHERE)
        {
            sphere = (t_sphere *)current->content;
            xs_list = ft_intersection(ray, *sphere, xs_list);
        }
        else if (((t_plane *)current->content)->type == PLANE)
        {
            plane = (t_plane *)current->content;
            xs_list = ft_intersect_plane(ray, *plane, xs_list);
        }
        // Add more cases here for other object types (e.g., CYLINDER, CONE, etc.)
        current = current->next;
    }
    return (xs_list);
}

void	ft_render_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_list	*intersections;

	intersections = NULL;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ft_create_ray(scene->camera->viewpoint, ft_create_vector(x - (WIDTH / 2), (HEIGHT / 2) - y, 5000));
			intersections = ft_intersect_objects(ray, scene->objects, intersections);
			mlx_put_pixel(scene->image, x, y, 0xFFFFFF);
			write(1, "olakease\n", 9);
			x++;
		}
		y++;
	}
	ft_lstclear(&intersections, free);
}
