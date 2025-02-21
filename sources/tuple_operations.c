/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:36:49 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/21 09:59:06 by igchurru         ###   ########.fr       */
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

t_tuple	*ft_multiply_tuple(t_tuple *tuple, float scalar)
{
	t_tuple	*multiplied;

	multiplied->x = tuple->x * scalar;
	multiplied->y = tuple->y * scalar;
	multiplied->z = tuple->z * scalar;
	multiplied->w = tuple->w;
	return (multiplied);
}

t_tuple	*ft_divide_tuple(t_tuple *tuple, float scalar)
{
	t_tuple	*divided;

	divided->x = tuple->x / scalar;
	divided->y = tuple->y / scalar;
	divided->z = tuple->z / scalar;
	divided->w = tuple->w;
	return (divided);
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
