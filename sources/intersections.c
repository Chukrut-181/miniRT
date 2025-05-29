/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: igchurru <igchurru@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/07 12:59:10 by igchurru		  #+#	#+#			 */
/*   Updated: 2025/05/13 14:02:58 by eandres          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minirt.h"

bool	intersect_plane(t_shape *shape, t_list **inter)
{
	t_xs	intersec;

	if (fabs(shape->ray_in_obj_space.direction.y) < EPSILON)
	{
		intersec.time = 0;
		return (false);
	}
	intersec.hit = 1;
	intersec.time = -1 * shape->ray_in_obj_space.origin.y
		/ shape->ray_in_obj_space.direction.y;
	if (intersec.time > EPSILON)
		update_inter(inter, shape, intersec.time);
	else
		return (false);
	return (true);
}

bool	intersect_cylinder(t_shape *shape, t_list **inter, t_ray ray)
{
	t_abcd	data;
	double	t[2];
	double	y0;
	double	y1;
	double	temp;

	abcd_for_cyl(&data, ray);
	if (data.discriminant < 0)
		return (false);
	solve_quadratic_equation(data, t);
	if (t[0] > t[1])
	{
		temp = t[0];
		t[0] = t[1];
		t[1] = temp;
	}
	y0 = ray.origin.y + t[0] * ray.direction.y;
	if (t[0] > EPSILON && y0 >= 0 && y0 <= 1)
		update_inter(inter, shape, t[0]);
	y1 = ray.origin.y + t[1] * ray.direction.y;
	if (t[1] > EPSILON && y1 >= 0 && y1 <= 1)
		update_inter(inter, shape, t[1]);
	return (true);
}

bool	intersect_sphere(t_shape *shape, t_list **inter)
{
	t_tuple	sphere_to_ray;
	t_tuple	origin;
	t_abcd	data;
	double	t[2];

	origin = ft_create_point(0, 0, 0);
	sphere_to_ray = substract_tuples(shape->ray_in_obj_space.origin, origin);
	data.a = dot_product(shape->ray_in_obj_space.direction,
			shape->ray_in_obj_space.direction);
	data.b = 2 * dot_product(shape->ray_in_obj_space.direction, sphere_to_ray);
	data.c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	data.discriminant = (data.b * data.b) - (4 * data.a * data.c);
	if (data.discriminant < 0)
		return (false);
	solve_quadratic_equation(data, t);
	if (t[0] >= EPSILON)
		update_inter(inter, shape, t[0]);
	if (t[1] >= EPSILON)
		update_inter(inter, shape, t[1]);
	return (true);
}

bool	ft_intersections(t_ray ray, t_shape *shape, t_list **inter)
{
	shape->ray_in_obj_space = transform(ray, shape->inverse_matrix);
	if (shape->type == SPHERE)
		return (intersect_sphere(shape, inter));
	else if (shape->type == PLANE)
		return (intersect_plane(shape, inter));
	else if (shape->type == CYLINDER)
		return (intersect_cylinder(shape, inter, shape->ray_in_obj_space));
	return (false);
}
