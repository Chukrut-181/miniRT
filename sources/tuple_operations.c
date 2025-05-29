/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:36:49 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 12:19:50 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple	add_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	addition;

	addition.x = tuple1.x + tuple2.x;
	addition.y = tuple1.y + tuple2.y;
	addition.z = tuple1.z + tuple2.z;
	addition.w = tuple1.w + tuple2.w;
	return (addition);
}

t_tuple	substract_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	substraction;

	substraction.x = tuple1.x - tuple2.x;
	substraction.y = tuple1.y - tuple2.y;
	substraction.z = tuple1.z - tuple2.z;
	substraction.w = tuple1.w - tuple2.w;
	return (substraction);
}

t_tuple	multiply_tuple_f(t_tuple tuple, double scalar)
{
	t_tuple	product;

	product.x = tuple.x * scalar;
	product.y = tuple.y * scalar;
	product.z = tuple.z * scalar;
	product.w = tuple.w * scalar;
	return (product);
}

t_tuple	divide_tuple(t_tuple tuple, double scalar)
{
	t_tuple	quotient;

	quotient.x = tuple.x / scalar;
	quotient.y = tuple.y / scalar;
	quotient.z = tuple.z / scalar;
	quotient.w = tuple.w;
	return (quotient);
}

t_tuple	multiply_tuples(t_tuple c1, t_tuple c2)
{
	t_tuple	result;

	result.x = c1.x * c2.x;
	result.y = c1.y * c2.y;
	result.z = c1.z * c2.z;
	return (result);
}
