/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:46:24 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/18 11:25:09 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

uint32_t	ft_color_to_argb(t_tuple color)
{
	return (((uint32_t)(color.x * 255) << 24) | ((uint32_t)(color.y * 255) << 16) | ((uint32_t)(color.z * 255) << 8)  | 0xFF);  
}

t_light	ft_switch_on_light(t_tuple source, t_tuple intensity)
{
	t_light	spotlight;

	spotlight.position = source;
	spotlight.intensity = intensity;
	return (spotlight);
}

t_material	ft_create_material(float x, float y, float z)
{
	t_material	m;

	m.color = ft_create_point(x, y, z);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 100.0;
	return (m);
}

t_tuple	ft_reflect(t_tuple incoming, t_tuple normal)
{
	t_tuple	reflection;
	
	reflection = ft_substract_tuples(incoming, ft_multiply_tuple(normal, 2 * ft_dot_product(incoming, normal)));
	return (reflection);
}

t_tuple	ft_normal_at_sphere_surface(t_sphere sphere, t_tuple world_point)
{
	t_tuple	normal;
	t_tuple	object_point;
	t_4x4	aux;
	
	aux = ft_find_inverse(*sphere.transform);
	object_point = ft_multiply_mat_and_tuple(aux, world_point);
	normal = ft_normalize(ft_substract_tuples(object_point, sphere.center));
	aux = ft_transpose(aux);
	normal = ft_multiply_mat_and_tuple(aux, normal);
	normal.w = 0;
	return (normal);
}

t_tuple	ft_illuminate(t_material material, t_light ligth, t_tuple point, t_tuple normal, t_tuple eye_vector)
{
	t_tuple	light_vector;
	t_tuple	reflection_vector;
	t_tuple	phong_ads[3];
	float	dot_light_normal;
	float	dot_reflection_eye;

	light_vector = ft_normalize(ft_substract_tuples(ligth.position, point));
	phong_ads[0] = ft_multiply_tuple(ft_multiply_colors(material.color, ligth.intensity), material.ambient);
	dot_light_normal = ft_dot_product(light_vector, normal);
	if (dot_light_normal < 0)
	{
		phong_ads[1] = ft_create_point(0, 0, 0);
		phong_ads[2] = ft_create_point(0, 0, 0);
		dot_reflection_eye = 0.0;
	}
	else
	{
		phong_ads[1] = ft_multiply_tuple(ft_multiply_colors(material.color, ligth.intensity), material.diffuse * dot_light_normal);
		reflection_vector = ft_reflect(ft_negate_tuple(light_vector), normal);
		dot_reflection_eye = ft_dot_product(reflection_vector, eye_vector);
	}
	if (dot_reflection_eye <= 0)
		phong_ads[2] = ft_create_point(0, 0, 0);
	else
		phong_ads[2] = ft_multiply_tuple(ligth.intensity, (material.specular * powf(dot_reflection_eye, material.shininess)));
	return (ft_add_tuples(phong_ads[0], ft_add_tuples(phong_ads[1], phong_ads[2])));
}

void	ft_render_billiard_ball(mlx_image_t *image)
{
	t_sphere	*ball;
	t_light		point_light;
	t_4x4		aux;
	t_ray		ray;
	t_list		*xs_list;
	t_xs		*temp;
	t_tuple		normal;
	t_tuple		eye_vector;
	t_tuple		color;
	int			x;
	int			y;

	ball = ft_create_sphere(ft_create_point(0, 0, 0), 100);
	ball->material = ft_create_material(200, 100, 100);
	point_light = ft_switch_on_light(ft_create_point(-500, 500, -1000), ft_create_point(1, 1, 1));
	aux = ft_multiply_matrices(create_translation_mx(ft_create_point(1200, 900, 0)), create_scalation_mx(ft_create_point(10, 10, 10)));
	ball->transform = malloc(sizeof(t_4x4));
	ball->transform = &aux;
	ray.origin = ft_create_point(0, 0, -500);
	x = 0;
	while (x < 2400)
	{
		y = 0;
		while (y < 1800)
		{	
			ray.direction = ft_create_vector(x - 1200, 900 - y, 1000);
			xs_list = ft_intersection(ray, *ball, NULL);
			while (xs_list)
			{
				temp = (t_xs *)xs_list->content;
				if (temp->hit == 1)
				{
					normal = ft_normal_at_sphere_surface(*ball, temp->point);
					eye_vector = ft_normalize(ft_negate_tuple(ray.direction));
					color = ft_illuminate(ball->material, point_light, temp->point, normal, eye_vector);
					mlx_put_pixel(image, x, y, ft_color_to_argb(color));
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
