/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tuples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:08:59 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/20 15:32:12 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple	*ft_create_point(float x, float y, float z)
{
	t_tuple	*new_point;

	new_point->x = x;
	new_point->y = y;
	new_point->z = z;
	new_point->w = 1;
	return (new_point);
}

t_tuple	*ft_create_vector(float x, float y, float z)
{
	t_tuple	*new_vector;

	new_vector->x = x;
	new_vector->y = y;
	new_vector->z = z;
	new_vector->w = 0;
	return (new_vector);
}

t_tuple	*ft_add_tuples(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*addition;

	addition->x = tuple1->x + tuple2->x;
	addition->y = tuple1->y + tuple2->y;
	addition->z = tuple1->z + tuple2->z;
	addition->w = tuple1->w + tuple2->w;
	return (addition);
}

t_tuple	*ft_substract_tuples(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*substraction;

	substraction->x = tuple1->x - tuple2->x;
	substraction->y = tuple1->y - tuple2->y;
	substraction->z = tuple1->z - tuple2->z;
	substraction->w = tuple1->w - tuple2->w;
	return (substraction);
}

int	ft_check_equality(t_tuple *tuple1, t_tuple *tuple2)
{
	if ((abs(tuple1->x - tuple2->x) < EPSILON)
		&& (abs(tuple1->y - tuple2->y) < EPSILON)
		&& (abs(tuple1->z - tuple2->z) < EPSILON))
		return (0);
	else
		return (1);
}
