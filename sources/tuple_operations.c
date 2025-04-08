/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:36:49 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/08 11:10:32 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
 * ft_add_tuples - Adds two t_tuple structures component-wise.
 *
 * tuple1: The first tuple to add.
 * tuple2: The second tuple to add.
 *
 * This function performs component-wise addition of two t_tuple
 * structures. Each corresponding x, y, z, and w component is added
 * together to produce a new t_tuple structure.
 *
 * Return: A t_tuple structure representing the sum of the input tuples.
 */
t_tuple	ft_add_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	addition;

	addition.x = tuple1.x + tuple2.x;
	addition.y = tuple1.y + tuple2.y;
	addition.z = tuple1.z + tuple2.z;
	addition.w = tuple1.w + tuple2.w;
	return (addition);
}

t_color	ft_add_color(t_color tuple1, t_color tuple2)
{
	t_color	addition;

	addition.r = tuple1.r + tuple2.r;
	addition.g = tuple1.g + tuple2.g;
	addition.b = tuple1.b + tuple2.b;
	return (addition);
}

/*
 * ft_substract_tuples - Subtracts one t_tuple structure from another.
 *
 * tuple1: The tuple to subtract from (minuend).
 * tuple2: The tuple to subtract (subtrahend).
 *
 * This function performs component-wise subtraction of two t_tuple
 * structures. Each corresponding x, y, z, and w component of tuple2
 * is subtracted from tuple1 to produce a new t_tuple structure.
 *
 * Return: A t_tuple structure representing the difference between
 *         the input tuples.
 */
t_tuple	ft_substract_tuples(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	substraction;

	substraction.x = tuple1.x - tuple2.x;
	substraction.y = tuple1.y - tuple2.y;
	substraction.z = tuple1.z - tuple2.z;
	substraction.w = tuple1.w - tuple2.w;
	return (substraction);
}

/*
 * ft_multiply_tuple - Multiplies each component of a t_tuple by a scalar.
 *
 * tuple: The tuple to be scaled.
 * scalar: The scalar value to multiply each component by.
 *
 * This function multiplies the x, y, and z components of the given
 * t_tuple by the provided scalar value. The 'w' component remains
 * unchanged, as it represents the distinction between a point and
 * a vector in homogeneous coordinates.
 *
 * Return: A t_tuple structure representing the scaled tuple.
 */
t_tuple	ft_multiply_tuple_f(t_tuple tuple, float scalar)
{
	t_tuple	product;

	product.x = tuple.x * scalar;
	product.y = tuple.y * scalar;
	product.z = tuple.z * scalar;
	product.w = tuple.w;
	return (product);
}

t_color	ft_multiply_color_f(t_color tuple, float scalar)
{
	t_color	product;

	product.r = tuple.r * scalar;
	product.g = tuple.g * scalar;
	product.b = tuple.b * scalar;
	return (product);
}

/**
 * ft_divide_tuple - Divides each component of a 4D tuple by a scalar value.
 * 
 * This function takes a tuple of four floating-point values (`tuple`) and
 * divides each of the `x`, `y`, and `z` components by a scalar value
 * (`scalar`). The `w` component remains unchanged. The function returns
 * a new tuple with the calculated quotient values for `x`, `y`, and `z`,
 * and the original `w` value.
 *
 * param tuple: A t_tuple structure containing the 4D vector to be divided.
 * param scalar: The scalar value by which the components of the tuple will
 *               be divided.
 * 
 * Return: A new t_tuple structure with the quotient values for `x`, `y`, and
 *         `z`, and the unchanged `w` value.
 */
t_tuple	ft_divide_tuple(t_tuple tuple, float scalar)
{
	t_tuple	quotient;

	quotient.x = tuple.x / scalar;
	quotient.y = tuple.y / scalar;
	quotient.z = tuple.z / scalar;
	quotient.w = tuple.w;
	return (quotient);
}

/**
 * ft_negate_tuple - Negates each component of a 4D tuple.
 * 
 * This function takes a tuple of four floating-point values (`tuple`) and
 * negates the `x`, `y`, and `z` components by multiplying each by -1. The
 * `w` component remains unchanged. The function returns a new tuple with the
 * negated values for `x`, `y`, and `z`, and the original `w` value.
 *
 * param tuple: A t_tuple structure containing the 4D vector to be negated.
 * 
 * Return: A new t_tuple structure with the negated values for `x`, `y`, and
 *         `z`, and the unchanged `w` value.
 */
t_tuple	ft_negate_tuple(t_tuple tuple)
{
	t_tuple	negated;

	negated.x = tuple.x * -1;
	negated.y = tuple.y * -1;
	negated.z = tuple.z * -1;
	negated.w = tuple.w;
	return (negated);
}

/**
 * ft_multiply_color - Multiplies corresponding components of two color tuples.
 * 
 * The function multiplies the `x`, `y`, and `z` components of the two tuples 
 * together. The `w` component is omitted from the result.
 *
 * param c1: The first t_tuple representing the first color.
 * param c2: The second t_tuple representing the second color.
 * 
 * Return: A new t_tuple containing the product of the `x`, `y`, and `z`.
 */
t_tuple	ft_multiply_tuple(t_tuple c1, t_tuple c2)
{
	t_tuple	result;

	result.x = c1.x * c2.x;
	result.y = c1.y * c2.y;
	result.z = c1.z * c2.z;
	return (result);
}

t_color	ft_multiply_color(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r * c2.r;
	result.g = c1.g * c2.g;
	result.b = c1.b * c2.b;
	return (result);
}
