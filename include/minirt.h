/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:28:29 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/21 11:28:37 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>

# define EPSILON 0.00001

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_tuple;

//	MAIN
int		main(int argc, char **argv);

//	MINIRT
int	ft_minirt(void);

//	HOOKS
void	ft_handle_key(mlx_key_data_t keydata, void *param);

// 	ERROR EXIT
int		ft_error_exit(char *err_msg, int err_code);

#endif
