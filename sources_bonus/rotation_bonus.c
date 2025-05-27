/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:23:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/26 12:52:33 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_4x4	rotation_x(float radians)
{
	t_4x4	rotation_x;

	rotation_x = create_identity_matrix();
	rotation_x.data[1][1] = cosf(radians);
	rotation_x.data[1][2] = -sinf(radians);
	rotation_x.data[2][1] = sinf(radians);
	rotation_x.data[2][2] = cosf(radians);
	return (rotation_x);
}

t_4x4	rotation_y(float radians)
{
	t_4x4	rotation_y;

	rotation_y = create_identity_matrix();
	rotation_y.data[0][0] = cosf(radians);
	rotation_y.data[0][2] = sinf(radians);
	rotation_y.data[2][0] = -sinf(radians);
	rotation_y.data[2][2] = cosf(radians);
	return (rotation_y);
}

t_4x4	rotation_z(float radians)
{
	t_4x4	rotation_z;

	rotation_z = create_identity_matrix();
	rotation_z.data[0][0] = cosf(radians);
	rotation_z.data[0][1] = -sinf(radians);
	rotation_z.data[1][0] = sinf(radians);
	rotation_z.data[1][1] = cosf(radians);
	return (rotation_z);
}

t_4x4	rodriguez_rotation(float target_x, float target_y, float target_z)
{
	t_tuple	target_n;
	t_tuple	axis;
	float	cos_th;
	float	sin_th;
	t_4x4	rot_mx;

	rot_mx = create_identity_matrix();
	target_n = normalize(create_vector(target_x, target_y, target_z));
	axis = normalize(cross_product(create_vector(0, 1, 0), target_n));
	cos_th = (0 * target_n.x) + (1 * target_n.y) + (0 * target_n.z);
	sin_th = get_magnitude(cross_product(create_vector(0, 1, 0), target_n));
	if (fabsf(sin_th) < EPSILON)
		return (rot_mx);
	rot_mx.data[0][0] = cos_th + axis.x * axis.x * (1.0f - cos_th);
	rot_mx.data[0][1] = axis.x * axis.y * (1.0f - cos_th) - axis.z * sin_th;
	rot_mx.data[0][2] = axis.x * axis.z * (1.0f - cos_th) + axis.y * sin_th;
	rot_mx.data[1][0] = axis.y * axis.x * (1.0f - cos_th) + axis.z * sin_th;
	rot_mx.data[1][1] = cos_th + axis.y * axis.y * (1.0f - cos_th);
	rot_mx.data[1][2] = axis.y * axis.z * (1.0f - cos_th) - axis.x * sin_th;
	rot_mx.data[2][0] = axis.z * axis.x * (1.0f - cos_th) - axis.y * sin_th;
	rot_mx.data[2][1] = axis.z * axis.y * (1.0f - cos_th) + axis.x * sin_th;
	rot_mx.data[2][2] = cos_th + axis.z * axis.z * (1.0f - cos_th);
	return (rot_mx);
}
