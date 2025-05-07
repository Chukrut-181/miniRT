/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:23:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/07 14:27:04 by igchurru         ###   ########.fr       */
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
t_4x4 ft_rotate_plane(float target_x, float target_y, float target_z)
{
    t_tuple initial_normal;
	t_tuple target_normal;
    t_tuple rotation_axis;
    float cos_theta;
    float sin_theta;
    t_4x4 rotation_matrix;

	initial_normal = ft_create_vector(0, 1, 0);
	target_normal = ft_normalize(ft_create_vector(target_x, target_y, target_z));

    // Calculate the axis of rotation
    rotation_axis = ft_normalize(ft_cross_product(initial_normal, target_normal));

    // Calculate the angle of rotation
    cos_theta = (initial_normal.x * target_normal.x) + (initial_normal.y * target_normal.y) + (initial_normal.z * target_normal.z);
    sin_theta = sqrtf(1.0f - cos_theta * cos_theta);

    // Handle the case where the normals are the same or opposite
    if (fabsf(sin_theta) < EPSILON)
    {
        if (cos_theta > 0)// No rotation needed, return identity
            return (ft_create_identity_matrix());
        else// 180 degree rotation around an arbitrary axis (e.g., X-axis)
        {
            rotation_matrix.data[0][0] = 1.0f;
            rotation_matrix.data[1][1] = -1.0f;
            rotation_matrix.data[2][2] = -1.0f;
            return (rotation_matrix);
        }
    }

    float kx = rotation_axis.x;
    float ky = rotation_axis.y;
    float kz = rotation_axis.z;
    float one_minus_cos = 1.0f - cos_theta;

    rotation_matrix.data[0][0] = cos_theta + kx * kx * one_minus_cos;
    rotation_matrix.data[0][1] = kx * ky * one_minus_cos - kz * sin_theta;
    rotation_matrix.data[0][2] = kx * kz * one_minus_cos + ky * sin_theta;
    rotation_matrix.data[0][3] = 0.0f;

    rotation_matrix.data[1][0] = ky * kx * one_minus_cos + kz * sin_theta;
    rotation_matrix.data[1][1] = cos_theta + ky * ky * one_minus_cos;
    rotation_matrix.data[1][2] = ky * kz * one_minus_cos - kx * sin_theta;
    rotation_matrix.data[1][3] = 0.0f;

    rotation_matrix.data[2][0] = kz * kx * one_minus_cos - ky * sin_theta;
    rotation_matrix.data[2][1] = kz * ky * one_minus_cos + kx * sin_theta;
    rotation_matrix.data[2][2] = cos_theta + kz * kz * one_minus_cos;
    rotation_matrix.data[2][3] = 0.0f;

    rotation_matrix.data[3][0] = 0.0f;
    rotation_matrix.data[3][1] = 0.0f;
    rotation_matrix.data[3][2] = 0.0f;
    rotation_matrix.data[3][3] = 1.0f;

    return (rotation_matrix);
}
