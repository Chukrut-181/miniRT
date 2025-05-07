/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:07:45 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/07 14:18:52 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* static bool	ft_apply_rgb_to_plane(t_plane *surface, char *rgb) {
	char	**split;
	float	aux;
	int		i;

	split = ft_split(rgb, ',');
	if (!split)
		return (false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]) / 255.0;
		if (aux < 0 || 1 < aux)
			return (free(split), false);
		if (i == 0)
			surface->material.color.r = aux;
		else if (i == 1)
			surface->material.color.g = aux;
		else if (i == 2)
			surface->material.color.b = aux;
		i++;
	}
	return (free(split), true);
} */

/* static bool	ft_apply_orientation_vector(t_plane *surface, char *n_n_vector)
{
	char	**split;
	float	aux;
	int		i;

	split = ft_split(n_n_vector, ',');
	if (!split)
		return (false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]);
		if (i == 0)
			surface->n_n_vector.x = aux;
		else if (i == 1)
			surface->n_n_vector.y = aux;
		else if (i == 2)
			surface->n_n_vector.z = aux;
		i++;
	}
	surface->n_n_vector.w = 0;
	ft_free_array(split);
	return (true);
} */

/* static bool	ft_set_plane_point(t_plane *surface, char *coords)
{
	char	**split;
	float	aux;
	int		i;

	split = ft_split(coords, ',');
	if (!split)
		return (false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]);
		if (i == 0)
			surface->point_in_plane.x = aux;
		else if (i == 1)
			surface->point_in_plane.y = aux;
		else if (i == 2)
			surface->point_in_plane.z = aux;
		i++;
	}
	surface->point_in_plane.w = 1;
	ft_free_array(split);
	return (true);
} */

int	ft_create_plane(t_scene *scene, char **surface)
{
	t_shape	*plane;
	char	**coords;
	t_4x4	translate;
	t_4x4	rotate;

	plane = malloc(sizeof(t_shape));
	if (!surface)
		return (1);
	plane->type = PLANE;
	if (!ft_check_coords(surface[1]))
		return (free(plane), 1);
	coords = ft_split(surface[1], ',');
	translate = create_translation_mx(ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2]));
	if (!ft_check_orientation_vector(surface[2]))
		return (free(plane), 1);
	ft_free_array(coords);
	coords = ft_split(surface[2], ',');
	rotate = ft_rotate_plane(ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2]));
	ft_free_array(coords);
	plane->transform_matrix = ft_multiply_matrices(translate, rotate);
	plane->inverse_matrix = ft_find_inverse(plane->transform_matrix);
	if (!ft_check_rgb(surface[3]))
		return (free(surface), 1);
	plane->material = ft_create_material(surface[3]);
	ft_lstadd_back((&scene->world->objects), ft_lstnew(plane));
	return (0);
}

