/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:41:59 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/07 11:55:23 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <time.h>
#include <limits.h>

static void	ft_print_4x4(t_4x4 *matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%12f ", matrix->data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

static t_4x4	*ft_randomize_matrix(void)
{
	t_4x4	*random_mx;
	float	temp;
	int		i;
	int		j;

	random_mx = ft_create_identity_matrix();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			temp = (rand() / 100000000) + (float)rand() / 10000000000;
			if (rand() % 2 == 0)
				temp = -temp;
			random_mx->data[i][j] = temp;
			j++;
		}
		i++;
	}
	return (random_mx);
}

int	ft_test_matrix_functions(void)
{
	t_4x4	*testmx1 = NULL;
	float	det_mx1;
	t_4x4	*invmx1 = NULL;
	float	det_inv1;
	t_4x4	*testmx2 = NULL;
	float	det_mx2;
	t_4x4	*invmx2 = NULL;
	float	det_inv2;
	t_4x4	*productmx = NULL;
	float	det_prodmx;
	t_4x4	*invprod = NULL;
	float	det_invprod;
	t_4x4	*product2mx = NULL;

	srand(time(NULL));
	testmx1 = ft_randomize_matrix();
	printf("This is testmx1:\n");
	ft_print_4x4(testmx1);
	det_mx1 = ft_calculate_determinant(testmx1);
	printf("It's determinant is %f\n\n", det_mx1);
	srand(time(NULL) - 100000);
	testmx2 = ft_randomize_matrix();
	printf("And this is testmx2:\n");
	ft_print_4x4(testmx2);
	det_mx2 = ft_calculate_determinant(testmx2);
	printf("It's determinant is %f\n\n", det_mx2);
	if (det_mx1 != 0)
	{
		invmx1 = ft_find_inverse(testmx1);
		printf("testmx1 can be inverted, and it's inverse is invmx1:\n");
		ft_print_4x4(invmx1);
		det_inv1 = ft_calculate_determinant(invmx1);
		printf("It's determinant is %f\n\n", det_inv1);
		productmx = ft_multiply_matrices(testmx1, invmx1);
		printf("And if we multiply testmx1 by it's inverse invmx1 we get:\n");
		ft_print_4x4(productmx);
		if (!ft_check_matrix_equality(productmx, ft_create_identity_matrix()))
			printf("Equality check OK: Result is an ID Matrix\n\n");
		else
			printf("Equality check NOT OK: Result is not an ID Matrix\n\n");
	}
	else
		printf("testmx1 cannot be inverted sice it's determinant is 0\n");
	if (det_mx2 != 0)
	{
		invmx2 = ft_find_inverse(testmx2);
		printf("testmx2 can be inverted, and it's inverse is invmx2:\n");
		ft_print_4x4(invmx2);
		det_inv2 = ft_calculate_determinant(invmx2);
		printf("It's determinant is %f\n\n", det_inv2);
		productmx = ft_multiply_matrices(testmx2, invmx2);
		printf("And if we multiply testmx2 by it's inverse invmx2 we get:\n");
		ft_print_4x4(productmx);
		if (!ft_check_matrix_equality(productmx, ft_create_identity_matrix()))
			printf("Equality check OK: Result is an ID Matrix\n\n");
		else
			printf("Equality check NOT OK: Result is not an ID Matrix\n\n");
	}
	else
		printf("testmx2 cannot be inverted sice it's determinant is 0\n");
	productmx = ft_multiply_matrices(testmx1, testmx2);
	printf("If we multiply testmx1 and testmx2 we get:\n");
	ft_print_4x4(productmx);
	det_prodmx = ft_calculate_determinant(productmx);
	printf("It's determinant is %f\n\n", det_prodmx);
	if (det_prodmx != 0)
	{
		invprod = ft_find_inverse(productmx);
		printf("productmx can be inverted, and it's inverse is invprod:\n");
		ft_print_4x4(invprod);
		det_invprod = ft_calculate_determinant(invprod);
		printf("It's determinant is %f\n\n", det_invprod);
		product2mx = ft_multiply_matrices(productmx, invprod);
		printf("If we multiply productmx by it's inverse invprod we get:\n");
		ft_print_4x4(product2mx);
		if (!ft_check_matrix_equality(product2mx, ft_create_identity_matrix()))
			printf("Equality check OK: Result is an ID Matrix\n\n");
		else
			printf("Equality check NOT OK: Result is not an ID Matrix\n\n");
	}
	else
		printf("productmx cannot be inverted sice it's determinant is 0\n");
	free(testmx1);
	free(testmx2);
	free(invmx1);
	free(invmx2);
	free(productmx);
	free(invprod);
	free(product2mx);
	return (0);
}
