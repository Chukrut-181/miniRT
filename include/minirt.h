/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:28:29 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/24 10:38:16 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>

# define EPSILON 0.00001

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_tuple;

//	MAIN
void	ft_draw_large_pixel(mlx_image_t	*image, int x, int y, int size);
void	ft_minigun(mlx_image_t	*image);
int		main(int argc, char **argv);

//	MINIRT
int	ft_minirt(void);

//	TUPLE CREATION
t_tuple	ft_create_point(float x, float y, float z);
t_tuple	ft_create_vector(float x, float y, float z);
int		ft_check_equality(t_tuple *tuple1, t_tuple *tuple2);

//	TUPLE OPERATIONS
t_tuple	ft_add_tuples(t_tuple *tuple1, t_tuple *tuple2);
t_tuple	ft_substract_tuples(t_tuple *tuple1, t_tuple *tuple2);
t_tuple	ft_multiply_tuple(t_tuple *tuple, float scalar);
t_tuple	ft_divide_tuple(t_tuple *tuple, float scalar);
t_tuple	ft_negate_tuple(t_tuple *tuple);

//	VECTOR OPERATIONS
float	ft_calculate_magnitude(t_tuple *v);
void	ft_normalize(t_tuple *v);
float	ft_dot_product(t_tuple *v1, t_tuple *v2);
t_tuple	ft_cross_product(t_tuple *v1, t_tuple *v2);

//	HOOKS
void	ft_handle_key(mlx_key_data_t keydata, void *param);

// 	ERROR EXIT
int		ft_error_exit(char *err_msg, int err_code);

#endif
