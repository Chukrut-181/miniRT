/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:36:49 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/03 16:03:35 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_tuple	ft_add_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	addition;

	addition.x = tuple1.x + tuple2.x;
	addition.y = tuple1.y + tuple2.y;
	addition.z = tuple1.z + tuple2.z;
	addition.w = tuple1.w + tuple2.w;
	return (addition);
}

t_tuple	ft_substract_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	substraction;

	substraction.x = tuple1.x - tuple2.x;
	substraction.y = tuple1.y - tuple2.y;
	substraction.z = tuple1.z - tuple2.z;
	substraction.w = tuple1.w - tuple2.w;
	return (substraction);
}

t_tuple	ft_multiply_tuple(t_tuple tuple, float scalar)
{
	t_tuple	product;

	product.x = tuple.x * scalar;
	product.y = tuple.y * scalar;
	product.z = tuple.z * scalar;
	product.w = tuple.w;

	return (product);
}

t_tuple	ft_divide_tuple(t_tuple tuple, float scalar)
{
	t_tuple	quotient;

	quotient.x = tuple.x / scalar;
	quotient.y = tuple.y / scalar;
	quotient.z = tuple.z / scalar;
	quotient.w = tuple.w;
	return (quotient);
}

t_tuple	ft_negate_tuple(t_tuple tuple)
{
	t_tuple	negated;

	negated.x = tuple.x * -1;
	negated.y = tuple.y * -1;
	negated.z = tuple.z * -1;
	negated.w = tuple.w;
	return (negated);
}

t_tuple ft_multiply_colors(t_tuple c1, t_tuple c2)
{
	t_tuple result;

	result.x = c1.x * c2.x;
	result.y = c1.y * c2.y;
	result.z = c1.z * c2.z;
	return (result);
}

