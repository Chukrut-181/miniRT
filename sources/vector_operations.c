/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:04:30 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/14 14:05:23 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/**
 *ft_calculate_magnitude - Calculates the magnitude (length) of a 3D vector.
 * 
 * This function computes the magnitude of a 3D vector using the Euclidean 
 * formula. The `w` component is ignored in the calculation. The result is
 * a floating-point value representing the length of the vector.
 *
 * param v: A t_tuple structure containing the 3D vector components. 
 * 
 * Return: A float representing the magnitude (length) of the vector `v`.
 */
float	ft_calculate_magnitude(t_tuple v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

/**
 * ft_normalize - Normalizes a 3D vector to have a magnitude of 1.
 * 
 * This function takes a 3D vector (`v`), calculates its magnitude using
 * the `ft_calculate_magnitude` function, and then divides each component
 * by the magnitude to normalize the vector.
 * The `w` component remains unchanged.
 * 
 * param v: A t_tuple structure containing the 3D vector to be normalized.
 * 
 * Return: A new t_tuple structure representing the normalized vector.
 */
t_tuple	ft_normalize(t_tuple v)
{
	float	mag;
	t_tuple	normalized;

	mag = ft_calculate_magnitude(v);
	normalized.x = v.x / mag;
	normalized.y = v.y / mag;
	normalized.z = v.z / mag;
	normalized.w = v.w;
	return (normalized);
}

/**
 * ft_dot_product - Computes the dot product of two 3D vectors.
 * 
 * This function calculates the dot product of two 3D vectors, `v1` and `v2`,
 * each represented by the `t_tuple` structure.The result is a floating-point
 * value that represents the scalar product of the two vectors.
 *
 * param v1: The first t_tuple structure representing the first 3D vector.
 * param v2: The second t_tuple structure representing the second 3D vector.
 * 
 * Return A float representing the dot product of the vectors `v1` and `v2`.
 */
float	ft_dot_product(t_tuple v1, t_tuple v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/**
 * ft_cross_product - Computes the cross product of two 3D vectors.
 * 
 * This function calculates the cross product of two 3D vectors, `v1` and `v2`,
 * each represented by the `t_tuple` structure. The cross product results in a
 * new vector that is perpendicular to both `v1` and `v2`.
 * The `w` component of the result is set to 0, as cross products in 3D space
 * yield a vector with three components. The resulting vector is returned.
 *
 * param v1: The first t_tuple structure representing the first 3D vector.
 * param v2: The second t_tuple structure representing the second 3D vector.
 * 
 * Return: A new t_tuple containing the cross product of `v1` and `v2`.
 */
t_tuple	ft_cross_product(t_tuple v1, t_tuple v2)
{
	t_tuple	cross_vector;

	cross_vector.x = v1.y * v2.z - v1.z * v2.y;
	cross_vector.y = v1.z * v2.x - v1.x * v2.z;
	cross_vector.z = v1.x * v2.y - v1.y * v2.x;
	cross_vector.w = 0;
	return (cross_vector);
}
