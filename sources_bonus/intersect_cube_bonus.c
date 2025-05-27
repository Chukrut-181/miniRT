/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cube_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:13:52 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/27 17:17:31 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// Helper function to calculate the intersection interval with a slab
static void calculate_slab_intersection(float origin, float direction, float min, float max, float *tmin, float *tmax)
{
	float tnumerator_min = min - origin;
	float tnumerator_max = max - origin;

	if (fabsf(direction) >= EPSILON)
	{
		*tmin = tnumerator_min / direction;
		*tmax = tnumerator_max / direction;
	}
	else
	{
		// Ray is parallel to the slab
		if (tnumerator_min > 0 || tnumerator_max < 0)
		{
			*tmin = FLT_MAX;
			*tmax = FLT_MIN;
		}
		else
		{
			*tmin = FLT_MIN;
			*tmax = FLT_MAX;
		}
	}

	if (*tmin > *tmax)
	{
		float temp = *tmin;
		*tmin = *tmax;
		*tmax = temp;
	}
}

bool    intersect_cube(t_shape *shape, t_list **inter, t_ray ray)
{
    float   xtmin, xtmax, ytmin, ytmax, ztmin, ztmax;
    float   tmin, tmax;

    // Calculate intersection intervals for each slab (x, y, z)
    calculate_slab_intersection(ray.origin.x, ray.direction.x, -1.0, 1.0, &xtmin, &xtmax);
    calculate_slab_intersection(ray.origin.y, ray.direction.y, -1.0, 1.0, &ytmin, &ytmax);
    calculate_slab_intersection(ray.origin.z, ray.direction.z, -1.0, 1.0, &ztmin, &ztmax);

    // Determine the overall entry and exit t values
    tmin = fmaxf(fmaxf(xtmin, ytmin), ztmin);
    tmax = fminf(fminf(xtmax, ytmax), ztmax);

    // If tmin > tmax, the ray does not intersect the cube
    if (tmin > tmax)
        return (false);

    // If tmax is not negative, we have an intersection
    if (tmax >= 0)
    {
        if (tmin >= 0)
            update_inter(inter, shape, tmin); // Entry point
        update_inter(inter, shape, tmax);     // Exit point
        return (true);
    }

    return (false);
}

