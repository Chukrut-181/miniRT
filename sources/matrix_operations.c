/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:50:24 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/26 13:32:33 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_check_matrix_equality(t_4x4 *matrix1, t_4x4 *matrix2)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (fabsf(matrix1->data[i][j] - matrix2->data[i][j]) > EPSILON)
				return (1);
			else
				j++;
		}
		i++;
	}
	return (0);
}

t_4x4	ft_multiply_matrices(t_4x4 *matrix1, t_4x4 *matrix2)
{
	t_4x4	multiplied;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			multiplied.data[i][j] = matrix1->data[i][0] * matrix2->data[0][j]
				+ matrix1->data[i][1] * matrix2->data[1][j]
				+ matrix1->data[i][2] * matrix2->data[2][j]
				+ matrix1->data[i][3] * matrix2->data[3][j];
			j++;
		}
		i++;
	}
	return (multiplied);
}

t_tuple	ft_multiply_mat_and_tuple(t_4x4 *matrix, t_tuple *tuple)
{
	t_tuple	multiplied;

	multiplied.x = matrix->data[0][0] * tuple->x + matrix->data[0][1] * tuple->y
		+ matrix->data[0][2] * tuple->z + matrix->data[0][3] * tuple->w;
	multiplied.y = matrix->data[1][0] * tuple->x + matrix->data[1][1] * tuple->y
		+ matrix->data[1][2] * tuple->z + matrix->data[1][3] * tuple->w;
	multiplied.z = matrix->data[2][0] * tuple->x + matrix->data[2][1] * tuple->y
		+ matrix->data[2][2] * tuple->z + matrix->data[2][3] * tuple->w;
	multiplied.w = matrix->data[3][0] * tuple->x + matrix->data[3][1] * tuple->y
		+ matrix->data[3][2] * tuple->z + matrix->data[3][3] * tuple->w;
	return (multiplied);
}

static void	ft_get_3x3_minor(t_4x4 *matrix, t_3x3 *submatrix, int row, int col)
{
	int	i;
	int	j;
	int	sub_i;
	int	sub_j;

	i = -1;
	sub_i = 0;
	while (++i < 4)
	{
		if (i != row)
		{
			sub_j = 0;
			j = -1;
			while (++j < 4)
			{
				if (j != col)
				{
					submatrix->data[sub_i][sub_j] = matrix->data[i][j];
					sub_j++;
				}
			}
			sub_i++;
		}
	}
}

t_4x4	ft_find_inverse(t_4x4 *matrix)
{
	t_4x4	inverse;
	t_3x3	submatrix;
	float	cofdet[2];
	int		row;
	int		col;

	cofdet[1] = ft_calculate_determinant(matrix);
	if (cofdet[1] == 0)
		return (*matrix);
	row = -1;
	while (++row < 4)
	{
		col = 0;
		while (col < 4)
		{
			ft_get_3x3_minor(matrix, &submatrix, row, col);
			cofdet[0] = ft_determinant_3x3(submatrix);
			if ((row + col) % 2 != 0)
				cofdet[0] = -cofdet[0];
			inverse.data[col][row] = cofdet[0] / cofdet[1];
			col++;
		}
	}
	return (inverse);
}
