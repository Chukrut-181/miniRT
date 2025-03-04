/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: igchurru <igchurru@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/19 13:09:24 by igchurru		  #+#	#+#			 */
/*   Updated: 2025/03/03 18:30:17 by eandres          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_minirt(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(2400, 1800, "miniRT", true);
	image = mlx_new_image(mlx, 2400, 1800);
	ft_test_matrix_functions();
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_key_hook(mlx, ft_handle_key, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

void	ft_draw_large_pixel(mlx_image_t	*image, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(image, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

void	ft_draw_clock(mlx_image_t *image)
{
	t_tuple		twelve_oclock;
	t_tuple		hour_position;
	t_4x4		*rotation_matrix;
	int			hour;
	double		angle;
	int			center_x;
	int			center_y;
	int			radius;
	
	// Set up the clock parameters
	center_x = image->width / 2;
	center_y = image->height / 2;
	radius = 500;  // Radius of the clock
	
	// Create the 12 o'clock position (top of the clock)
	twelve_oclock = ft_create_point(0, -radius, 0);
	ft_draw_large_pixel(image, center_x, center_y, 10);
	hour = 0;
	while (hour < 12)
	{
		angle = (float)hour * (2 * M_PI / 12);
		
		rotation_matrix = rotation_z(angle);

		hour_position = ft_multiply_mat_and_tuple(rotation_matrix, &twelve_oclock);
		ft_draw_large_pixel(image, (center_x/3) + (int)hour_position.x, (center_y/3) + (int)hour_position.y, 15);
		free(rotation_matrix);
		hour++;
	}
}
