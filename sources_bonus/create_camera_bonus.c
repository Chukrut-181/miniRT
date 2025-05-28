/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:51:00 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/28 11:56:45 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"

t_4x4	ft_orientation(t_tuple left, t_tuple true_up, t_tuple forward)
{
	t_4x4	matrix;

	matrix = create_identity_matrix();
	matrix.data[0][0] = left.x;
	matrix.data[0][1] = left.y;
	matrix.data[0][2] = left.z;
	matrix.data[1][0] = true_up.x;
	matrix.data[1][1] = true_up.y;
	matrix.data[1][2] = true_up.z;
	matrix.data[2][0] = -forward.x;
	matrix.data[2][1] = -forward.y;
	matrix.data[2][2] = -forward.z;
	return (matrix);
}

t_4x4	view_transform(t_tuple origin, t_tuple direction)
{
	t_tuple	left;
	t_tuple	up;
	t_tuple	true_up;
	t_4x4	orientation;
	t_4x4	translation;

	up = create_vector(0, 1, 0);
	if (fabsf(direction.y) > 0.9999f)
	{
		if (direction.y > 0)
			up = create_vector(0, 0, -1);
		else
			up = create_vector(0, 0, 1);
	}
	left = normalize(cross_product(direction, up));
	true_up = cross_product(left, direction);
	orientation = ft_orientation(left, true_up, direction);
	translation = create_translation_mx(-origin.x, -origin.y, -origin.z);
	return (multiply_matrices(orientation, translation));
}

static void	camera_guie(t_scene *scene, char *pov)
{
	float	fov;
	float	half_view;
	float	aspect;

	fov = ft_atof(pov) * M_PI / 180.0;
	scene->camera->field_of_view = fov;
	half_view = tanf(fov / 2);
	aspect = ((float)WIDTH / (float)HEIGHT);
	if (aspect >= 1)
	{
		scene->camera->half_width = half_view;
		scene->camera->half_height = half_view / aspect;
	}
	else
	{
		scene->camera->half_width = half_view * aspect;
		scene->camera->half_height = half_view;
	}
	scene->camera->pixel_size = (scene->camera->half_width * 2) / WIDTH;
}

bool	create_camera(t_scene *scene, char **cam_data)
{
	t_tuple	origin;
	t_tuple	direction;
	char	**coords;

	if (scene->camera != NULL)
		ft_error_exit(scene, "Error\nCamera defined twice", 1);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera || ft_arraylen(cam_data) != 4)
		return (false);
	if (!check_coords(cam_data[1]) || !check_coords(cam_data[2]))
		return (free(scene->camera), false);
	coords = ft_split(cam_data[1], ',');
	origin = ft_create_point(ft_atof(coords[0]),
			ft_atof(coords[1]), ft_atof(coords[2]));
	scene->camera->origin = origin;
	ft_free_array(coords);
	coords = ft_split(cam_data[2], ',');
	direction = create_vector(ft_atof(coords[0]),
			ft_atof(coords[1]), ft_atof(coords[2]));
	direction = normalize(direction);
	ft_free_array(coords);
	scene->camera->transform = view_transform(origin, direction);
	camera_guie(scene, cam_data[3]);
	return (true);
}
