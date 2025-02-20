/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:36:49 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/20 15:42:24 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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

t_tuple	*ft_scale_tuple(t_tuple *tuple, float scalar)
{
	t_tuple	*scaled;

	scaled->x = tuple->x * scalar;
	scaled->y = tuple->y * scalar;
	scaled->z = tuple->z * scalar;
	scaled->w = tuple->w;
	return (scaled);
}

t_tuple	*ft_negate_tuple(t_tuple *tuple)
{
	t_tuple	*negated;

	negated->x = tuple->x * -1;
	negated->y = tuple->y * -1;
	negated->z = tuple->z * -1;
	negated->w = tuple->w;
	return (negated);
}
