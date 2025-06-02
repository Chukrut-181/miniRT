/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:05:17 by igchurru          #+#    #+#             */
/*   Updated: 2025/06/02 10:41:12 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"

t_material	create_material(char *rgb_code)
{
	t_material	m;
	char		**split;

	m.ambient = 0.5;
	m.diffuse = 0.8;
	m.specular = 1;
	m.shininess = 200;
	split = ft_split(rgb_code, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		m.color = ft_create_color(1.0, 1.0, 1.0);
	else
		m.color = ft_create_color(ft_atof(split[0]) / 255,
				ft_atof(split[1]) / 255, ft_atof(split[2]) / 255);
	if (split)
		ft_free_array(split);
	return (m);
}

bool	create_sphere(t_scene *scene, char **ball)
{
	t_shape	*sphere;
	t_4x4	translate;
	t_4x4	scalate;
	char	**center;
	float	diameter;

	if (ft_arraylen(ball) != 4)
		return (false);
	sphere = malloc(sizeof(t_shape));
	if (!sphere)
		ft_error_exit(scene, "Error\nFailed to allocate sphere", 1);
	sphere->type = SPHERE;
	if (!check_coords(ball[1]) || !check_rgb(ball[3]))
		return (free(sphere), false);
	center = ft_split(ball[1], ',');
	translate = create_translation_mx(ft_atof(center[0]),
			ft_atof(center[1]), ft_atof(center[2]));
	diameter = ft_atof(ball[2]) / 2.0f;
	scalate = create_scaling_mx(diameter, diameter, diameter);
	sphere->material = create_material(ball[3]);
	sphere->transform_matrix = multiply_matrices(translate, scalate);
	sphere->inverse_matrix = find_inverse(sphere->transform_matrix);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(sphere));
	ft_free_array(center);
	return (true);
}
