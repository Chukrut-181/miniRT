/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2025/04/08 10:05:17 by igchurru          #+#    #+#             */ /*   Updated: 2025/04/11 10:56:56 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static bool	ft_apply_rgb_to_sphere(t_sphere *sphere, char *rgb)
{
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
			sphere->material.color.r = aux;
		else if (i == 1)
			sphere->material.color.g = aux;
		else if (i == 2)
			sphere->material.color.b = aux;
		i++;
	}
	return (free(split), true);
}

static bool	ft_set_sphere_center(t_sphere *sphere, char *coords)
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
			sphere->center.x = aux;
		else if (i == 1)
			sphere->center.y = aux;
		else if (i == 2)
			sphere->center.z = aux;
		i++;
	}
	sphere->center.w = 1;
	ft_free_array(split);
	return (true);
}

int	ft_create_sphere(t_scene *scene, char **ball)
{
	t_sphere	*sphere;
	t_list		*new_node;
	float		aux;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	sphere->type = SPHERE;
	if (!ft_check_coords(ball[1]))
		return (free(sphere), 1);
	if (!ft_set_sphere_center(sphere, ball[1]))
		return (free(sphere), 1);
	aux = ft_atof(ball[2]);
	sphere->diameter = aux;
	if (!ft_check_rgb(ball[3]))
		return (free(sphere), 1);
	if (!ft_apply_rgb_to_sphere(sphere, ball[3]))
		return (free(sphere), 1);
	new_node = ft_lstnew(sphere);
	if (!new_node)
		return (free(sphere), 1);
	sphere->transform = ft_create_identity_matrix();
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.3;
	sphere->material.shininess = 100.0;
	ft_lstadd_back(&(scene->objects), new_node);
	return (0);
}

