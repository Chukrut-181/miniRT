/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:23:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/07 15:08:22 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_4x4	rotation_x(float radians)
{
	t_4x4	rotation_x;

	rotation_x = ft_create_identity_matrix();
	rotation_x.data[1][1] = cosf(radians);
	rotation_x.data[1][2] = -sinf(radians);
	rotation_x.data[2][1] = sinf(radians);
	rotation_x.data[2][2] = cosf(radians);
	return (rotation_x);
}

t_4x4	rotation_y(float radians)
{
	t_4x4	rotation_y;

	rotation_y = ft_create_identity_matrix();
	rotation_y.data[0][0] = cosf(radians);
	rotation_y.data[0][2] = sinf(radians);
	rotation_y.data[2][0] = -sinf(radians);
	rotation_y.data[2][2] = cosf(radians);
	return (rotation_y);
}

t_4x4	rotation_z(float radians)
{
	t_4x4	rotation_z;

	rotation_z = ft_create_identity_matrix();
	rotation_z.data[0][0] = cosf(radians);
	rotation_z.data[0][1] = -sinf(radians);
	rotation_z.data[1][0] = sinf(radians);
	rotation_z.data[1][1] = cosf(radians);
	return (rotation_z);
}

// Function to create the rotation matrix to align (0, 1, 0) to target_normal
/* t_4x4 ft_rotate_plane(t_tuple normal)
{
	double		angle;
	double		vals[3];
	t_tuple 	axis;
	t_4x4		rotation;

	rotation = ft_create_identity_matrix();
	angle = acos(ft_dot_product(normal, ft_create_vector(0, 1, 0)));
	axis = ft_cross_product(ft_create_vector(normal.x, normal.y, normal.z), ft_create_vector(0, 1, 0));
	vals[0] = cos(angle);
	vals[1] = sin(angle);
	vals[2] = 1.0 - vals[0];
	rotation.data[0][0] = vals[0] + (pow(axis.x, 2) * vals[2]);
	rotation.data[0][1] = (axis.x * axis.y * vals[2]) - (axis.z * vals[1]);
	rotation.data[0][2] = (axis.x * axis.z * vals[2]) + (axis.y * vals[1]);
	rotation.data[1][0] = (axis.y * axis.z * vals[2]) + (axis.z * vals[1]);
	rotation.data[1][1] = vals[0] + (pow(axis.y, 2) * vals[2]);
	rotation.data[1][2] = (axis.y * axis.z * vals[2]) - (axis.x * vals[1]);
	rotation.data[2][0] = (axis.z * axis.x * vals[2]) - (axis.y * vals[1]);
	rotation.data[2][1] = (axis.z * axis.y * vals[2]) + (axis.x * vals[1]);
	rotation.data[2][2] = vals[0] + (pow(axis.z, 2) * vals[2]);
	rotation.data[3][3] = 1;
	return (rotation);
} */

t_4x4 ft_rotate_plane(t_tuple normal)
{
	t_tuple		axis;
	double		angle;
	double		cos_angle;
	double		sin_angle;
	double		one_minus_cos;
	t_4x4		rotation;
	t_tuple		reference;
	
	normal = ft_normalize(normal);
	reference = ft_create_vector(0, 1, 0);
	cos_angle = ft_dot_product(normal, reference);
	rotation = ft_create_identity_matrix();
	if (fabs(cos_angle) > 0.9999f)
	{
		if (cos_angle > 0)
			return (rotation);
		rotation.data[1][1] = -1;
		rotation.data[2][2] = -1;
		return (rotation);
	}
	axis = ft_normalize(ft_cross_product(reference, normal));
	angle = acos(cos_angle);
	sin_angle = sin(angle);
	one_minus_cos = 1.0f - cos_angle;
	rotation.data[0][0] = cos_angle + axis.x * axis.x * one_minus_cos;
	rotation.data[0][1] = axis.x * axis.y * one_minus_cos - axis.z * sin_angle;
	rotation.data[0][2] = axis.x * axis.z * one_minus_cos + axis.y * sin_angle;
	rotation.data[1][0] = axis.y * axis.x * one_minus_cos + axis.z * sin_angle;
	rotation.data[1][1] = cos_angle + axis.y * axis.y * one_minus_cos;
	rotation.data[1][2] = axis.y * axis.z * one_minus_cos - axis.x * sin_angle;
	rotation.data[2][0] = axis.z * axis.x * one_minus_cos - axis.y * sin_angle;
	rotation.data[2][1] = axis.z * axis.y * one_minus_cos + axis.x * sin_angle;
	rotation.data[2][2] = cos_angle + axis.z * axis.z * one_minus_cos;
	return (rotation);
}
