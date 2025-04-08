/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:08:59 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/08 11:01:03 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
 * ft_create_point - Creates a point in a 3D space using the given
 *                   coordinates (x, y, z).
 *
 * @x: The x-coordinate of the point.
 * @y: The y-coordinate of the point.
 * @z: The z-coordinate of the point.
 *
 * This function initializes a t_tuple structure with the provided
 * x, y, and z values. The 'w' component is set to 1, which
 * indicates that the tuple represents a point (not a vector) in
 * homogeneous coordinates.
 *
 * Return: A t_tuple structure representing a point in 3D space.
 */
t_color	ft_create_color(float x, float y, float z)
{
	t_color	new_point;

	new_point.r = x;
	new_point.g = y;
	new_point.b = z;
	return (new_point);
}

t_tuple	ft_create_point(float x, float y, float z)
{
	t_tuple	new_point;

	new_point.x = x;
	new_point.y = y;
	new_point.z = z;
	new_point.w = 1;
	return (new_point);
}

/*
 * ft_create_vector - Creates a vector in a 3D space using the given
 *                    components (x, y, z).
 *
 * @x: The x-component of the vector.
 * @y: The y-component of the vector.
 * @z: The z-component of the vector.
 *
 * This function initializes a t_tuple structure with the provided
 * x, y, and z values. The 'w' component is set to 0, which
 * indicates that the tuple represents a vector (not a point) in
 * homogeneous coordinates.
 *
 * Return: A t_tuple structure representing a vector in 3D space.
 */
t_tuple	ft_create_vector(float x, float y, float z)
{
	t_tuple	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	new_vector.w = 0;
	return (new_vector);
}

/**
 * ft_check_equality - 	Compares two t_tuple structures for equality
 * 						within a small tolerance.
 * 
 * This function checks if the x, y, and z components of two given t_tuple 
 * structures are approximately equal within the defined EPSILON threshold.
 * This approach accounts for floating-point precision errors.
 * 
 * param tuple1: The first tuple to compare.
 * param tuple2: The second tuple to compare.
 * 
 * Return: Returns 0 if the tuples are considered equal within EPSILON,
 *         otherwise returns 1.
 */
int	ft_check_equality(t_tuple tuple1, t_tuple tuple2)
{
	if ((fabsf(tuple1.x - tuple2.x) < EPSILON)
		&& (fabsf(tuple1.y - tuple2.y) < EPSILON)
		&& (fabsf(tuple1.z - tuple2.z) < EPSILON))
		return (0);
	else
		return (1);
}
