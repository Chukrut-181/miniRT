/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:05:17 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/16 13:05:10 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_material	ft_create_material(char *rgb_code)
{
	t_material	m;
	char		**split;

	m.ambient = 0.2;
	m.diffuse = 0.7;
	m.specular = 0.9;
	m.shininess = 199.0;
	split = ft_split(rgb_code, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		m.color = ft_create_color(1.0, 1.0, 1.0);
	else
		m.color = ft_create_color((ft_atof(split[0]) / 255.0),
				(ft_atof(split[1]) / 255.0), (ft_atof(split[2]) / 255.0));
	if (split)
		ft_free_array(split);
	return (m);
}

static t_4x4	ft_transform_sphere(char *center, float radius)
{
	t_4x4	translate;
	t_4x4	scalate;
	t_4x4	transform;
	char	**aux;

	aux = ft_split(center, ',');
	translate = create_translation_mx(ft_atof(aux[0]),
			ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	scalate = create_scaling_mx(radius, radius, radius);
	transform = ft_multiply_matrices(translate, scalate);
	return (transform);
}

bool	ft_create_sphere(t_scene *scene, char **ball)
{
	t_shape	*sphere;
	float	radius;

	sphere = malloc(sizeof(t_shape));
	if (!sphere)
		ft_error_exit(scene, "Failed to allocate memory for sphere", 1);
	sphere->type = SPHERE;
	if (!ft_check_coords(ball[1]))
		return (free(sphere), false);
	radius = ft_atof(ball[2]) / 2.0;
	if (radius <= EPSILON)
		return (free(sphere), false);
	sphere->transform_matrix = ft_transform_sphere(ball[1], radius);
	sphere->inverse_matrix = ft_find_inverse(sphere->transform_matrix);
	if (!ft_check_rgb(ball[3]))
		return (free(sphere), false);
	sphere->material = ft_create_material(ball[3]);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(sphere));
	return (true);
}
