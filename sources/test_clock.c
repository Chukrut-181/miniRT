/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_clock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:47:46 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/27 15:44:34 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minirt.h"

void	ft_draw_large_pixel(mlx_image_t	*image, int x, int y, int size)
{
	int	w;
	int	h;

	h = 0;
	while(h < size)
	{
		w = 0;
		while (w < size)
		{
			mlx_put_pixel(image, x + w, (1800 - y + h), 0xFF0000FF);
			w++;
		}
		h++;
	}
}

void	ft_draw_clock(mlx_image_t *image)
{
	t_tuple center;
	t_tuple translate;
	t_4x4	translation_matrix;
	t_tuple	new_center;

	center = ft_create_point(0, 0, 0);										// Declaro el centro en 0.0.0
	translate = ft_create_point(1200, 900, 0);								// Valor de la traslacion: Mitad del ancho y del alto
	translation_matrix = *translation(&translate);							// Aplicar valor de traslación sobre la matriz ID. -> Se obtiene matriz de traslación
	new_center = ft_multiply_mat_and_tuple(&translation_matrix, &center);	// Punto trasladado = matriz de traslación  * punto original
	ft_draw_large_pixel(image, new_center.x, new_center.y, 25);				// Renderizar.
}

