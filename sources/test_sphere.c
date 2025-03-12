/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:57:06 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/12 10:23:00 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* static t_ray	ft_transform_ray(t_ray ray, t_4x4 *m)
{
	t_ray	transformed;

	transformed.origin = *ft_multiply_mat_and_tuple(m, &ray.origin);
	transformed.direction = *ft_multiply_mat_and_tuple(m, &ray.direction);
	return (transformed);
}

static t_4x4 *ft_transformation_test(void)
{
	t_4x4	*transform;

	transform =  NULL;
	transform = ft_find_inverse(create_scalation_mx(ft_create_point(0.25, 1, 1)));
	if (!transform)
		return (write(1, "matriz caca\n", 12), NULL);
	return (transform);
} */

void	ft_render_sphere(mlx_image_t *image)
{
	t_sphere	sphere;
	t_ray		ray;
	t_tuple		ray_origin;
	t_tuple		direction;
	t_list		*xs_list;
	t_xs		*aux;
	int			x;
	int			y;

	sphere = *ft_create_sphere(*ft_create_point(0, 0, 0), 10);
	ray_origin = *ft_create_point(0, 0, -100);
	xs_list = NULL;
	x = 0;
	while (x < 2400)
	{
		y = 0;
		while (y < 1800)
		{	
			direction = *ft_create_vector(x - 1200, 900 - y, 5000);
			ft_normalize(&direction);
			ray = ft_create_ray(ray_origin, direction);
			//ray = ft_transform_ray(ray, ft_transformation_test());
			xs_list = ft_intersection(ray, sphere, xs_list);
			while (xs_list)
			{
				aux = (t_xs *)xs_list->content;
				if (aux->hit == 1)
				{
					mlx_put_pixel(image, x, y, 0xFFFFFFFF);
					break ;
				}
				xs_list = xs_list->next;
			}
			ft_lstclear(&xs_list, free);
			y++;
		}
		x++;
	}
}
