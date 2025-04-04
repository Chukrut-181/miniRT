/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:43:31 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/04 12:25:29 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static bool	ft_apply_rgb_to_cylinder(t_cyl *cylinder, char *rgb)
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
			cylinder->material.color.r = aux;
		else if (i == 1)
			cylinder->material.color.g = aux;
		else if (i == 2)
			cylinder->material.color.b = aux;
		i++;
	}
	return (free(split), true);
}

static bool	ft_set_cylinder_axis_orientation(t_cyl *cylinder, char *orientation)
{
	char	**split;
	int		i;
	float	aux;

	split = ft_split(orientation, ',');
	if (ft_arraylen(split) > 3)
		return (ft_free_array(split), false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]);
		if (aux < -1 || 1 < aux)
			return (ft_free_array(split), false);
		else if (i == 0)
			cylinder->axis_vector.x = aux;
		else if (i == 1)
			cylinder->axis_vector.y = aux;
		else if (i == 2)
			cylinder->axis_vector.z = aux;
		i++;
	}
	cylinder->axis_vector.w = 0;
	return (ft_free_array(split), true);
}

static bool	ft_set_cylinder_center(t_cyl *cylinder, char *coords)
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
		if(i == 0)
			cylinder->center.x = aux;
		else if (i == 1)
			cylinder->center.y = aux;
		else if (i == 2)
			cylinder->center.z = aux;
		i++;
	}
	cylinder->center.w = 1;
	ft_free_array(split);
	return (true);
}

int	ft_create_cylinder(t_scene *scene, char **cyl)
{

	t_cyl	*cylinder;
	t_list	*new_node;
	float	aux;
	
	cylinder = malloc(sizeof(t_cyl));
	if (!cylinder)
		return (1);
	cylinder->type = CYLINDER;
	if (!ft_check_coords(cyl[1]) || !ft_set_cylinder_center(cylinder, cyl[1]))
		return (free(cylinder), 1);
	if (!ft_set_cylinder_axis_orientation(cylinder, cyl[2]))
		return (free(cylinder), 1);
	aux = ft_atof(cyl[3]);
	cylinder->diameter = aux;
	aux = ft_atof(cyl[4]);
	cylinder->height = aux;
	if (!ft_check_rgb(cyl[5]) || !ft_apply_rgb_to_cylinder(cylinder, cyl[5]))
		return (free(cylinder), 1);
	new_node = ft_lstnew(cylinder);
	if (!new_node)
		return (free(cylinder), 1);
	ft_lstadd_back(&(scene->objects), new_node);
	return (0);
}
