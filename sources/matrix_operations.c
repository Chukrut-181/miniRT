/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:50:24 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/12 12:48:37 by eandres          ###   ########.fr       */
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

t_4x4	*ft_multiply_matrices(t_4x4 *mat1, t_4x4 *mat2)
{
	t_4x4	*product;
	int		i;
	int		j;

	product = malloc(sizeof(t_4x4));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			product->data[i][j] = mat1->data[i][0] * mat2->data[0][j]
				+ mat1->data[i][1] * mat2->data[1][j]
				+ mat1->data[i][2] * mat2->data[2][j]
				+ mat1->data[i][3] * mat2->data[3][j];
			j++;
		}
		i++;
	}
	return (product);
}

t_tuple	*ft_multiply_mat_and_tuple(t_4x4 *mat, t_tuple *tuple)
{
	t_tuple	*product;

	product = malloc(sizeof(t_tuple));
	product->x = mat->data[0][0] * tuple->x + mat->data[0][1] * tuple->y
		+ mat->data[0][2] * tuple->z + mat->data[0][3] * tuple->w;
	product->y = mat->data[1][0] * tuple->x + mat->data[1][1] * tuple->y
		+ mat->data[1][2] * tuple->z + mat->data[1][3] * tuple->w;
	product->z = mat->data[2][0] * tuple->x + mat->data[2][1] * tuple->y
		+ mat->data[2][2] * tuple->z + mat->data[2][3] * tuple->w;
	product->w = mat->data[3][0] * tuple->x + mat->data[3][1] * tuple->y
		+ mat->data[3][2] * tuple->z + mat->data[3][3] * tuple->w;
	return (product);
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

t_4x4	*ft_find_inverse(t_4x4 *matrix)
{
	t_4x4	*inverse;
	t_3x3	submatrix;
	float	cofdet[2];
	int		row;
	int		col;

	inverse = malloc(sizeof(t_4x4));
	cofdet[1] = ft_calculate_determinant(matrix);
	if (cofdet[1] == 0)
		return (matrix);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
		{
			ft_get_3x3_minor(matrix, &submatrix, row, col);
			cofdet[0] = ft_determinant_3x3(submatrix);
			if ((row + col) % 2 != 0)
				cofdet[0] = -cofdet[0];
			inverse->data[col][row] = cofdet[0] / cofdet[1];
		}
	}
	return (inverse);
}
