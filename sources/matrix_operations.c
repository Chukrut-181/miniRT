/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:50:24 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/21 11:24:44 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/**
 * ft_check_matrix_equality - 	Checks if two 4x4 matrices are equal
 * 								within a given tolerance.
 * 
 * This function compares two 4x4 matrices element by element.
 * If all elements are sufficiently close (i.e., the difference is less than
 * or equal to `EPSILON`), the matrices are considered equal.
 * 
 * param matrix1: The first t_4x4 structure representing the first matrix.
 * param matrix2: The second t_4x4 structure representing the second matrix.
 * 
 * Return: `1` if the matrices are not equal, and `0` if they are equal within 
 *         the specified tolerance (`EPSILON`).
 */
int	ft_check_matrix_equality(t_4x4 matrix1, t_4x4 matrix2)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (fabsf(matrix1.data[i][j] - matrix2.data[i][j]) > EPSILON)
				return (1);
			else
				j++;
		}
		i++;
	}
	return (0);
}

/**
 * multiply_matrices - Multiplies two 4x4 matrices.
 * 
 * This function performs matrix multiplication according to the standard
 * matrix multiplication rules, where each element in the resulting matrix
 * is the sum of the products of the corresponding elements in the rows
 * of the first matrix and the columns of the second matrix.
 * 
 * param mat1: The first t_4x4 matrix to be multiplied.
 * param mat2: The second t_4x4 matrix to be multiplied.
 * 
 * Return: A t_4x4 structure representing the product of `mat1` and `mat2`.
 */
t_4x4	multiply_matrices(t_4x4 mat1, t_4x4 mat2)
{
	t_4x4	product;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			product.data[i][j] = mat1.data[i][0] * mat2.data[0][j]
				+ mat1.data[i][1] * mat2.data[1][j]
				+ mat1.data[i][2] * mat2.data[2][j]
				+ mat1.data[i][3] * mat2.data[3][j];
		}
	}
	return (product);
}

/**
 * ft_multiply_mat_and_tuple - Multiplies a 4x4 matrix by a 4D tuple.
 *  
 * This function performs matrix-vector multiplication between a 4x4 matrix
 * and a 4D tuple (`tuple`), where each component of the resulting tuple
 * is the sum of the products of the corresponding row of the matrix and the 
 * components of the tuple.
 * 
 * param mat: A t_4x4 matrix.
 * param tuple: A t_tuple structure representing the 4D vector to be multiplied.
 * 
 * Return A t_tuple representing the product of the matrix and the tuple.
 */
t_tuple	ft_multiply_mat_and_tuple(t_4x4 mat, t_tuple tuple)
{
	t_tuple	product;

	product.x = mat.data[0][0] * tuple.x + mat.data[0][1] * tuple.y
		+ mat.data[0][2] * tuple.z + mat.data[0][3] * tuple.w;
	product.y = mat.data[1][0] * tuple.x + mat.data[1][1] * tuple.y
		+ mat.data[1][2] * tuple.z + mat.data[1][3] * tuple.w;
	product.z = mat.data[2][0] * tuple.x + mat.data[2][1] * tuple.y
		+ mat.data[2][2] * tuple.z + mat.data[2][3] * tuple.w;
	product.w = mat.data[3][0] * tuple.x + mat.data[3][1] * tuple.y
		+ mat.data[3][2] * tuple.z + mat.data[3][3] * tuple.w;
	return (product);
}

/**
 * t_get_3x3_minor - 	Extracts a 3x3 minor matrix from a 4x4 matrix
 * 						by removing a row and a column.
 * 
 * This function calculates the 3x3 minor matrix by removing a specific row
 * and column from the given 4x4 matrix.
 * 
 * param matrix: A t_4x4 structure representing the original 4x4 matrix.
 * param row: The index of the row to be removed from the matrix (0 to 3).
 * param col: The index of the column to be removed from the matrix (0 to 3).
 * 
 * Return A t_3x3 structure representing the 3x3 minor matrix.
 */
static t_3x3	ft_get_3x3_minor(t_4x4 matrix, int row, int col)
{
	int		i[2];
	int		sub_i;
	int		sub_j;
	t_3x3	submatrix;

	i[0] = -1;
	sub_i = 0;
	while (++i[0] < 4)
	{
		if (i[0] != row)
		{
			sub_j = 0;
			i[1] = -1;
			while (++i[1] < 4)
			{
				if (i[1] != col)
				{
					submatrix.data[sub_i][sub_j] = matrix.data[i[0]][i[1]];
					sub_j++;
				}
			}
			sub_i++;
		}
	}
	return (submatrix);
}

/**
 * ft_find_inverse - Calculates the inverse of a 4x4 matrix.
 * 
 * This function computes the inverse of a 4x4 matrix using the method of 
 * cofactors and determinants. It first calculates the determinant of the 
 * input matrix. If the determinant is zero, the matrix is not invertible.
 * 
 * param matrix: A t_4x4 structure representing the matrix to be inverted.
 * 
 * Return: A t_4x4 structure representing the inverse of the matrix if the 
 *         determinant is non-zero, otherwise returns the original matrix.
 */
t_4x4	ft_find_inverse(t_4x4 matrix)
{
	t_4x4	inverse;
	t_3x3	submatrix;
	float	cofdet[2];
	int		row;
	int		col;

	cofdet[1] = ft_calculate_determinant(matrix);
	if (cofdet[1] == 0)
		return (matrix);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
		{
			submatrix = ft_get_3x3_minor(matrix, row, col);
			cofdet[0] = ft_determinant_3x3(submatrix);
			if ((row + col) % 2 != 0)
				cofdet[0] = -cofdet[0];
			inverse.data[col][row] = cofdet[0] / cofdet[1];
		}
	}
	return (inverse);
}
