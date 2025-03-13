/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:04:30 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/13 14:16:14 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* The distance represented by a vector is called its magnitude, or length.
It’s how far you would travel in a straight line if you were to walk from
one end of the vector to the other. */
float	ft_calculate_magnitude(t_tuple v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

/* Vectors with magnitudes of 1 are called unit vectors. Normalization is the
process of taking an arbitrary vector and converting it into a unit vector. */
t_tuple	ft_normalize(t_tuple v)
{
	float	mag;
	t_tuple	normalized;
	

	mag = ft_calculate_magnitude(v);
	normalized.x /= mag;
	normalized.y /= mag;
	normalized.z /= mag;
	return (normalized);
}

/* The dot product takes two vectors and returns a scalar value.
The smaller the dot product, the larger the angle between the vectors.
Given two unit vectors, a dot product of 1 means the vectors are identical,
and a dot product of -1 means they point in opposite directions.
Specifically, and again if the two vectors are unit vectors, the dot product
is actually the cosine of the angle between them. */
float	ft_dot_product(t_tuple v1, t_tuple v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/* This function 'creates' a new vector that is perpendicular to both the
original vectors. Note that this is specifically testing vectors, not tuples.
Also, note that if you change the order of the operands, you change the
direction of the resulting vector. Order matters!
X cross Y gives you Z, but Y cross X gives you -Z! */
t_tuple	ft_cross_product(t_tuple v1, t_tuple v2)
{
	t_tuple	cross_vector;

	cross_vector.x = v1.y * v2.z - v1.z * v2.y;
	cross_vector.y = v1.z * v2.x - v1.x * v2.z;
	cross_vector.z = v1.x * v2.y - v1.y * v2.x;
	cross_vector.w = 0;
	return (cross_vector);
}
