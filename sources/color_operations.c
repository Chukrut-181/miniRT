/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:57:23 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/21 11:30:28 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_color	multiply_colors(t_color c1, t_color c2)
{
	t_color	result;

	result.r = c1.r * c2.r;
	if (result.r > 255)
		result.r = 255;
	result.g = c1.g * c2.g;
	if (result.g > 255)
		result.g = 255;
	result.b = c1.b * c2.b;
	if (result.b > 255)
		result.b = 255;
	return (result);
}

t_color	multiply_color_f(t_color tuple, float scalar)
{
	t_color	product;

	product.r = tuple.r * scalar;
	product.g = tuple.g * scalar;
	product.b = tuple.b * scalar;
	return (product);
}

t_color	add_colors(t_color tuple1, t_color tuple2)
{
	t_color	addition;

	addition.r = tuple1.r + tuple2.r;
	addition.g = tuple1.g + tuple2.g;
	addition.b = tuple1.b + tuple2.b;
	return (addition);
}

t_color	ft_create_color(float x, float y, float z)
{
	t_color	new_point;

	new_point.r = x;
	new_point.g = y;
	new_point.b = z;
	return (new_point);
}

t_tuple	color_tp(t_color p)
{
	t_tuple	tp;

	tp = ft_create_point(p.r, p.g, p.b);
	return (tp);
}
