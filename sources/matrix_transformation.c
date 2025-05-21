/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:23:12 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/21 11:31:04 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/**
 * create_identity_matrix - Creates a 4x4 identity matrix.
 * 
 * This function initializes a 4x4 matrix and sets it to be an identity matrix.
 * Takes no parameters.
 *
 * Return: A t_4x4 structure representing the identity matrix:
 * 
 *         | 1 0 0 0 |
 *         | 0 1 0 0 |
 *         | 0 0 1 0 |
 *         | 0 0 0 1 |
 */
t_4x4	create_identity_matrix(void)
{
	t_4x4	idmatrix;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				idmatrix.data[i][j] = 1;
			else
				idmatrix.data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (idmatrix);
}

/**
 * create_translation_mx - Creates a 4x4 translation matrix based on a 3D tuple.
 * 
 * This function generates a 4x4 translation matrix that will translate a 3D 
 * point by the values specified in the `tuple` structure.
 * 
 * param tuple: A t_tuple structure containing the translation values for the 
 *              `x`, `y`, and `z` components.
 * 
 * Return: A t_4x4 structure representing the translation matrix:
 * 
 *         | 1 0 0 tuple.x |
 *         | 0 1 0 tuple.y |
 *         | 0 0 1 tuple.z |
 *         | 0 0 0   1     |
 */
t_4x4	create_translation_mx(float x, float y, float z)
{
	t_4x4	translation_mx;

	translation_mx = create_identity_matrix();
	translation_mx.data[0][3] = x;
	translation_mx.data[1][3] = y;
	translation_mx.data[2][3] = z;
	return (translation_mx);
}

/**
 * create_scalation_mx - Creates a 4x4 scaling matrix based on a 3D tuple.
 * 
 * This function generates a 4x4 scaling matrix that will scale a 3D point by 
 * the values specified in the `tuple` structure.
 * 
 * param tuple: A t_tuple structure containing the scaling factors for the 
 *              `x`, `y`, and `z` components.
 * 
 * Return: A t_4x4 structure representing the scaling matrix:
 * 
 *         | tuple.x 0      0      0 |
 *         | 0      tuple.y 0      0 |
 *         | 0      0      tuple.z 0 |
 *         | 0      0      0      1 |
 */
t_4x4	create_scaling_mx(float x, float y, float z)
{
	t_4x4	scaling_mx;

	scaling_mx = create_identity_matrix();
	scaling_mx.data[0][0] = x;
	scaling_mx.data[1][1] = y;
	scaling_mx.data[2][2] = z;
	return (scaling_mx);
}

/**
 * ft_create_shearing_mx - 	Creates a 4x4 shearing matrix based on
 * 							given shear factors.
 * 
 * This function generates a 4x4 shearing matrix for 3D transformations.
 * Shearing is a transformation that distorts the shape of an object,
 * shifting its components along one axis based on values from another axis.
 * 
 * param Xy: Shear factor for the x-axis with respect to the y-axis.
 * param Xz: Shear factor for the x-axis with respect to the z-axis.
 * param Yx: Shear factor for the y-axis with respect to the x-axis.
 * param Yz: Shear factor for the y-axis with respect to the z-axis.
 * param Zx: Shear factor for the z-axis with respect to the x-axis.
 * param Zy: Shear factor for the z-axis with respect to the y-axis.
 * 
 * Return: A t_4x4 structure representing the shearing matrix:
 * 
 *         | 1 Xy Xz 0 |
 *         | Yx 1 Yz 0 |
 *         | Zx Zy 1 0 |
 *         | 0  0  0 1 |
 */
/* t_4x4	ft_create_shearing_mx
		(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy)
{
	t_4x4	shearing_mx;

	shearing_mx = create_identity_matrix();
	shearing_mx.data[0][1] = Xy;
	shearing_mx.data[0][2] = Xz;
	shearing_mx.data[1][0] = Yx;
	shearing_mx.data[1][2] = Yz;
	shearing_mx.data[2][0] = Zx;
	shearing_mx.data[2][1] = Zy;
	return (shearing_mx);
} */
