/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:05:17 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/13 13:15:35 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_material	ft_create_material(char *rgb_code)
{
	t_material m;
	char **split;

	m.ambient = 0.2;
	m.diffuse = 0.7;
	m.specular = 0.9;
	m.shininess = 200;
	split = ft_split(rgb_code, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		m.color = ft_create_color(1.0, 1.0, 1.0);
	else
		m.color = ft_create_color(ft_atof(split[0]) / 255, ft_atof(split[1]) / 255, ft_atof(split[2]) / 255);
	m.a_color = m.color;
	if (split)
		ft_free_array(split);
	return (m);
}

int	ft_create_sphere(t_scene *scene, char **ball)
{
	t_shape	*sphere;
	t_4x4	translate;
	t_4x4	scalate;
	char	**center;
	float	diameter;

	sphere = malloc(sizeof(t_shape));
	if (!sphere)
		return (1);
	sphere->type = SPHERE;
	if (!ft_check_coords(ball[1]))
		return (free(sphere), 1);
	center = ft_split(ball[1], ',');
	translate = create_translation_mx(ft_atof(center[0]),
			ft_atof(center[1]), ft_atof(center[2]));
	diameter = ft_atof(ball[2]);
	scalate = create_scaling_mx(diameter, diameter, diameter);
	if (!ft_check_rgb(ball[3]))
		return (free(sphere), 1);
	sphere->material = ft_create_material(ball[3]);
	sphere->transform_matrix = ft_multiply_matrices(translate, scalate);
	sphere->inverse_matrix = ft_find_inverse(sphere->transform_matrix);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(sphere));
	ft_free_array(center);
	return (0);
}
