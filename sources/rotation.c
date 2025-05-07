/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:23:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/07 10:32:51 by igchurru         ###   ########.fr       */
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
t_4x4 ft_rotate_plane(float target_normal[3])
{
    float initial_normal[3] = {0.0f, 1.0f, 0.0f};
    float rotation_axis[3];
    float cos_theta;
    float sin_theta;
    t_4x4 rotation_matrix;

    // Normalize the target normal
    normalize_vector(target_normal);

    // Calculate the axis of rotation
    vector_cross(initial_normal, target_normal, rotation_axis);
    normalize_vector(rotation_axis);

    // Calculate the angle of rotation
    cos_theta = initial_normal[0] * target_normal[0] +
                initial_normal[1] * target_normal[1] +
                initial_normal[2] * target_normal[2];
    sin_theta = sqrtf(1.0f - cos_theta * cos_theta); // sin(acos(x))

    // Handle the case where the normals are the same or opposite
    if (fabsf(sin_theta) < 1e-6)
    {
        if (cos_theta > 0)
        {
            // No rotation needed, return identity
            return (rotation_matrix);
        }
        else
        {
            // 180 degree rotation around an arbitrary axis (e.g., X-axis)
            rotation_matrix.data[0][0] = 1.0f;
            rotation_matrix.data[1][1] = -1.0f;
            rotation_matrix.data[2][2] = -1.0f;
            return (rotation_matrix);
        }
    }

    float kx = rotation_axis[0];
    float ky = rotation_axis[1];
    float kz = rotation_axis[2];
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
