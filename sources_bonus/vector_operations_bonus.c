/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:04:30 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 12:19:50 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"

double	get_magnitude(t_tuple v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_tuple	normalize(t_tuple v)
{
	double	mag;
	t_tuple	normalized;

	mag = get_magnitude(v);
	normalized.x = v.x / mag;
	normalized.y = v.y / mag;
	normalized.z = v.z / mag;
	return (normalized);
}

double	dot_product(t_tuple v1, t_tuple v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_tuple	cross_product(t_tuple v1, t_tuple v2)
{
	t_tuple	cross_vector;

	cross_vector.x = v1.y * v2.z - v1.z * v2.y;
	cross_vector.y = v1.z * v2.x - v1.x * v2.z;
	cross_vector.z = v1.x * v2.y - v1.y * v2.x;
	cross_vector.w = 0;
	return (cross_vector);
}
