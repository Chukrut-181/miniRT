/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:59:20 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/15 13:47:37 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static bool	ft_set_center(t_tuple *center, char *coords)
{
	char	**temp;

	temp = ft_split(coords, ',');
	if (ft_arraylen(temp) != 3)
		return (ft_free_array(temp), false);
	center->x = ft_atof(temp[0]);
	center->y = ft_atof(temp[1]);
	center->z = ft_atof(temp[2]);
	center->w = 1;
	ft_free_array(temp);
	return (true);
}

static void	ft_apply_and_enlist(t_scene *s, t_tuple p, float d, t_object *obj)
{
	t_4x4	translation_mx;
	t_4x4	scalation_mx;
	t_tuple	scale_values;

	translation_mx = create_translation_mx(p);
	scale_values = ft_create_vector(d / 2, d / 2, d / 2);
	scalation_mx = create_scalation_mx(scale_values);
	obj->transform = ft_multiply_matrices(translation_mx, scalation_mx);
	ft_lstadd_back((t_list **)&s->objects, ft_lstnew(obj));
}

int	ft_create_sphere(t_scene *scene, char **data)
{
	t_tuple		center;
	float		diameter;
	t_object	*new_sphere;

	new_sphere = (t_object *)malloc(sizeof(t_object));
	if (!new_sphere)
		return (1);
	new_sphere->type = SPHERE;
	if (!ft_check_coords(data[1]) || !ft_set_center(&center, data[1]))
		return (1);
	diameter = ft_atof(data[2]);
	if (!ft_check_rgb(data[3]) || !ft_apply_rgb(&new_sphere->color, data[3]))
		return (1);
	ft_apply_and_enlist(scene, center, diameter, new_sphere);
	return (0);
}
