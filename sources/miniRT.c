/* ************************************************************************** */
/*																			*/ /*														:::	  ::::::::   */ /*   miniRT.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: igchurru <igchurru@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/19 13:09:24 by igchurru		  #+#	#+#			 */
/*   Updated: 2025/03/04 15:22:31 by eandres		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../include/minirt.h"

int ft_minirt(void)
{
	mlx_t *mlx;
	mlx_image_t *image;

	mlx = mlx_init(800, 600, "miniRT - Simple Scene", true);
	if (!mlx)
		return (1);
	image = mlx_new_image(mlx, 800, 600);
	if (!image)
	{
		mlx_terminate(mlx);
		return (1);
	}
	render_lit_sphere(image);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_key_hook(mlx, ft_handle_key, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

//int	ft_minirt(void)
//{
//	mlx_t		*mlx;
//	mlx_image_t	*image;
//
//	mlx = mlx_init(800, 600, "miniRT", true);
//	image = mlx_new_image(mlx, 800, 600);
//	scene(image);
////	test_default_world();
////	render_lit_sphere(image);
//	//ft_minigun(image);
//	//ft_draw_clock(image);
//	//ft_render_sphere(image);
//	mlx_image_to_window(mlx, image, 0, 0);
//	mlx_key_hook(mlx, ft_handle_key, mlx);
//	mlx_loop(mlx);
//	mlx_terminate(mlx);
//	return (0);
//}

/* void	ft_draw_large_pixel(mlx_image_t	*image, int x, int y, int size)
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
} */

