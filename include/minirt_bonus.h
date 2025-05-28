/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:51:26 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/28 11:53:19 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "minirt.h"

//	CREATE CUBE
bool	create_cube(t_scene *scene, char **temp);
bool	intersect_cube(t_shape *shape, t_list **inter, t_ray ray);

#endif