/* ************************************************************************** */
/*																			*/ /*														:::	  ::::::::   */ /*   miniRT.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: igchurru <igchurru@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/19 13:09:24 by igchurru		  #+#	#+#			 */
/*   Updated: 2025/03/04 15:22:31 by eandres          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minirt.h"

static	void	ft_draw_semi_circule(mlx_image_t *image);
static void	ft_draw_dock(mlx_image_t *image);
static void	ft_draw_line_up(mlx_image_t *image);

int	ft_minirt(void)
{
	mlx_t		*mlx; mlx_image_t	*image;

	mlx = mlx_init(2400, 1800, "miniRT", true);
	image = mlx_new_image(mlx, 2400, 1800);
	//ft_minigun(image);
	//ft_test_matrix_functions();
	//ft_draw_clock(image);
	//ft_test_ray();
	//ft_test_intersection();
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
	t_4x4		*translation_matrix;
	t_4x4		*transformation_matrix;
	int		hour;
	double		angle;
	int		center_x;
	int		center_y;
	int		radius;
	
	// Set up the clock parameters
	center_x = image->width / 2;
	center_y = image->height / 1.5;
	radius = 200;  // Radius of the clock
	translation_matrix = create_translation_mx(ft_create_point(image->width / 2, image->height / 1.5, 0));
	// Create the 12 o'clock position (top of the clock)
	twelve_oclock = *ft_create_point(0, -radius, 0);
	hour = 0;
	while (hour < 12)
	{
		angle = (float)hour * (2 * M_PI / 12);
		
		rotation_matrix = rotation_z(angle);
		transformation_matrix = ft_multiply_matrices(translation_matrix, rotation_matrix);
		hour_position = *ft_multiply_mat_and_tuple(transformation_matrix, &twelve_oclock);
		printf("hourX = %f, hourY = %f\n", hour_position.x, hour_position.y);
		ft_draw_large_pixel(image, (int)hour_position.x, (int)hour_position.y, 15);
		free(rotation_matrix);
		hour++;
	}
}
//
//static void	ft_draw_dock(mlx_image_t *image)
//{
//	ft_draw_clock(image);
//	t_tuple		twelve_oclock;
//	t_tuple		hour_position;
//	t_4x4		*rotation_matrix;
//	t_4x4		*translation_matrix;
//	t_4x4		*transformation_matrix;
//	int		hour;
//	double		angle;
//	int		center_x;
//	int		center_y;
//	int		radius;
//	
//	// Set up the clock parameters
//	radius = 200;  // Radius of the clock
//	center_x = 1500 + radius;
//	center_y = 1200;
//	translation_matrix = create_translation_mx(ft_create_point(center_x, center_y, 0));
//	// Create the 12 o'clock position (top of the clock)
//	twelve_oclock = *ft_create_point(0, -radius, 0);
//	hour = 0;
//	while (hour < 12)
//	{
//		angle = (float)hour * (2 * M_PI / 12);
//		
//		rotation_matrix = rotation_z(angle);
//		transformation_matrix = ft_multiply_matrices(translation_matrix, rotation_matrix);
//		hour_position = *ft_multiply_mat_and_tuple(transformation_matrix, &twelve_oclock);
//		printf("hourX = %f, hourY = %f\n", hour_position.x, hour_position.y);
//		ft_draw_large_pixel(image, (int)hour_position.x, (int)hour_position.y, 15);
//		free(rotation_matrix);
//		hour++;
//	}
//	ft_draw_line_up(image);
//	ft_draw_semi_circule(image);
//}
//
//static	void	ft_draw_semi_circule(mlx_image_t *image)
//{
//	t_tuple		twelve_oclock;
//	t_tuple		hour_position;
//	t_4x4		*rotation_matrix;
//	t_4x4		*translation_matrix;
//	t_4x4		*transformation_matrix;
//	int		hour;
//	double		angle;
//	int		center_x;
//	int		center_y;
//	int		radius;
//	
//	// Set up the clock parameters
//	radius = 200;  // Radius of the clock
//	center_x = 1250 + radius;
//	center_y = 420;
//	translation_matrix = create_translation_mx(ft_create_point(center_x, center_y, 0));
//	// Create the 12 o'clock position (top of the clock)
//	twelve_oclock = *ft_create_point(0, -radius, 0);
//	hour = 0;
//	while (hour < 4)
//	{
//		angle = (float)hour * (2 * M_PI / 12);
//		
//		rotation_matrix = rotation_z(angle);
//		transformation_matrix = ft_multiply_matrices(translation_matrix, rotation_matrix);
//		hour_position = *ft_multiply_mat_and_tuple(transformation_matrix, &twelve_oclock);
//		printf("hourX = %f, hourY = %f\n", hour_position.x, hour_position.y);
//		ft_draw_large_pixel(image, (int)hour_position.x, (int)hour_position.y, 15);
//		free(rotation_matrix);
//		hour++;
//	}
//	hour = 0;
//	while (hour < 4)
//	{
//		angle = (float)hour * (2 * M_PI / 12);
//		
//		rotation_matrix = rotation_z(-angle);
//		transformation_matrix = ft_multiply_matrices(translation_matrix, rotation_matrix);
//		hour_position = *ft_multiply_mat_and_tuple(transformation_matrix, &twelve_oclock);
//		printf("hourX = %f, hourY = %f\n", hour_position.x, hour_position.y);
//		ft_draw_large_pixel(image, (int)hour_position.x, (int)hour_position.y, 15);
//		free(rotation_matrix);
//		hour++;
//	}
//}
//
//static void	ft_draw_line_up(mlx_image_t *image)
//{
//	int i = 0;
//	int large = 950;
//
//	while (i < 10)
//	{
//		ft_draw_large_pixel(image, 1250, large, 15);
//		ft_draw_large_pixel(image, 1650, large, 15);
//		large -= 50;
//		i++;
//	}
//	i = 0;
//	int len = 1250;
//	while (i < 9)
//	{
//		ft_draw_large_pixel(image, len, large, 15);
//		len += 50;
//		i++;
//	}
//}
//
