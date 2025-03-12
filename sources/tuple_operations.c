/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:36:49 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/12 12:52:06 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple	*ft_add_tuples(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*addition;

	addition = malloc(sizeof(t_tuple));
	if (!addition)
		return (NULL);
	addition->x = tuple1->x + tuple2->x;
	addition->y = tuple1->y + tuple2->y;
	addition->z = tuple1->z + tuple2->z;
	addition->w = tuple1->w + tuple2->w;
/* 	free(tuple1);
	free(tuple2);
	tuple1 = NULL;
	tuple2 = NULL; */
	return (addition);
}

t_tuple	*ft_substract_tuples(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*substraction;

	substraction = malloc(sizeof(t_tuple));
	if (!substraction)
		return (NULL);
	substraction->x = tuple1->x - tuple2->x;
	substraction->y = tuple1->y - tuple2->y;
	substraction->z = tuple1->z - tuple2->z;
	substraction->w = tuple1->w - tuple2->w;
/* 	free(tuple1);
	free(tuple2);
	tuple1 = NULL;
	tuple2 = NULL; */
	return (substraction);
}

t_tuple	*ft_multiply_tuple(t_tuple *tuple, float scalar)
{
	t_tuple	*product;

	product = malloc(sizeof(t_tuple));
	if (!product)
		return (NULL);
	product->x = tuple->x * scalar;
	product->y = tuple->y * scalar;
	product->z = tuple->z * scalar;
	product->w = tuple->w;
/* 	free(tuple);
	tuple = NULL; */
	return (product);
}

t_tuple	*ft_divide_tuple(t_tuple *tuple, float scalar)
{
	t_tuple	*quotient;

	quotient = malloc(sizeof(t_tuple));
	if (!quotient)
		return (NULL);
	quotient->x = tuple->x / scalar;
	quotient->y = tuple->y / scalar;
	quotient->z = tuple->z / scalar;
	quotient->w = tuple->w;
/* 	free(tuple);
	tuple = NULL; */
	return (quotient);
}

t_tuple	*ft_negate_tuple(t_tuple *tuple)
{
	t_tuple	*negated;

	negated = malloc(sizeof(t_tuple));
	if (!negated)
		return (NULL);
	negated->x = tuple->x * -1;
	negated->y = tuple->y * -1;
	negated->z = tuple->z * -1;
	negated->w = tuple->w;
/* 	free(tuple);
	tuple = NULL; */
	return (negated);
}
