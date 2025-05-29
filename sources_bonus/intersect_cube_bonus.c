/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:13:52 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 12:20:52 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"

static void	handle_parallel_slab(double tnum_min, double tnum_max,
	double *tmin, double *tmax)
{
	if (tnum_min > EPSILON || tnum_max < -EPSILON)
	{
		*tmin = INFINITY;
		*tmax = -INFINITY;
	}
	else
	{
		*tmin = -INFINITY;
		*tmax = INFINITY;
	}
}

static void	intersect_slab(double src, double dir, double *tmin, double *tmax)
{
	double	tnumerator_min;
	double	tnumerator_max;
	double	temp;

	tnumerator_min = -1.0f - src;
	tnumerator_max = 1.0f - src;
	if (fabs(dir) >= EPSILON)
	{
		*tmin = tnumerator_min / dir;
		*tmax = tnumerator_max / dir;
	}
	else
		handle_parallel_slab(tnumerator_min, tnumerator_max, tmin, tmax);
	if (*tmin > *tmax)
	{
		temp = *tmin;
		*tmin = *tmax;
		*tmax = temp;
	}
}

bool	intersect_cube(t_shape *shape, t_list **inter, t_ray ray)
{
	double	xt[2];
	double	yt[2];
	double	zt[2];
	double	tmin;
	double	tmax;

	intersect_slab(ray.origin.x, ray.direction.x, &xt[0], &xt[1]);
	intersect_slab(ray.origin.y, ray.direction.y, &yt[0], &yt[1]);
	intersect_slab(ray.origin.z, ray.direction.z, &zt[0], &zt[1]);
	tmin = fmaxf(fmaxf(xt[0], yt[0]), zt[0]);
	tmax = fminf(fminf(xt[1], yt[1]), zt[1]);
	if (tmin > tmax)
		return (false);
	if (tmax >= EPSILON)
	{
		if (tmin >= EPSILON)
			update_inter(inter, shape, tmin);
		update_inter(inter, shape, tmax);
		return (true);
	}
	return (false);
}
