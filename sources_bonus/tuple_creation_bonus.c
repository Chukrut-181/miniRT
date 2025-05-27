/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:08:59 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/26 13:42:37 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple	ft_create_point(float x, float y, float z)
{
	t_tuple	new_point;

	new_point.x = x;
	new_point.y = y;
	new_point.z = z;
	new_point.w = 1;
	return (new_point);
}

t_tuple	create_vector(float x, float y, float z)
{
	t_tuple	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	new_vector.w = 0;
	return (new_vector);
}

int	check_equality(t_tuple tuple1, t_tuple tuple2)
{
	if ((fabsf(tuple1.x - tuple2.x) < EPSILON)
		&& (fabsf(tuple1.y - tuple2.y) < EPSILON)
		&& (fabsf(tuple1.z - tuple2.z) < EPSILON))
		return (0);
	else
		return (1);
}

t_point	create_point(double x, double y, double z)
{
	t_point	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_tuple	negate_tuple(t_tuple tuple)
{
	t_tuple	negated;

	negated.x = tuple.x * -1;
	negated.y = tuple.y * -1;
	negated.z = tuple.z * -1;
	negated.w = tuple.w;
	return (negated);
}
