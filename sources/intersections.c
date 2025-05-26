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

// Helper function to solve the quadratic equation using t_abcd struct
static bool	quadratic_equation_solution(t_abcd *data, float *t)
{
	data->discriminant = data->b * data->b - 4 * data->a * data->c;
	if (data->discriminant < 0)
		return (false);
	t[0] = (-data->b - sqrtf(data->discriminant)) / (2 * data->a);
	t[1] = (-data->b + sqrtf(data->discriminant)) / (2 * data->a);
	return (true);
}

static	void	update_inter(t_list **inter, t_shape *shape, float time)
{
	t_xs	*intersec;

	intersec = malloc(sizeof(t_xs));
	if (!intersec)
		return ;
	intersec->object = shape;
	intersec->time = time;
	intersec->hit = 1;
	intersec->intersec = true;
	if (*inter == NULL)
		*inter = ft_lstnew(intersec);
	else
		ft_lstadd_back(inter, ft_lstnew(intersec));
}

bool	intersec_plane(t_shape *shape, t_list **inter)
{
	t_xs	intersec;

	if (fabsf(shape->ray_in_obj_space.direction.y) < EPSILON)
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
/* static void	ft_intersect_caps(t_shape *cyl, t_ray ray, t_list **xs_list)
{
	float t;
	t_tuple p;

	// Intersect with the bottom cap (y = 0 in object space)
	if (fabsf(ray.direction.y) < EPSILON)
		return;

	t = -ray.origin.y / ray.direction.y;
	if (t >= 0)
	{
		p = add_tuples(ray.origin, multiply_tuple_f(ray.direction, t));
		if (powf(p.x, 2) + powf(p.z, 2) <= 1) // Radius is 1 in object space
			update_inter(xs_list, cy_shape, t);
	}

	// Intersect with the top cap (y = 1 in object space)
	t = (1 - ray.origin.y) / ray.direction.y; // Height is 1 in object space
	if (t >= 0)
	{
		p = add_tuples(ray.origin, multiply_tuple_f(ray.direction, t));
		if (powf(p.x, 2) + powf(p.z, 2) <= 1) // Radius is 1 in object space
			update_inter(xs_list, cy_shape, t);
	}
} */

bool	intersec_cylinder(t_shape *shape, t_list **inter, t_ray ray)
{
	t_abcd	data;
	float	t[2];
	float	y0;
	float	y1;
	float	temp;

	data.a = powf(ray.direction.x, 2) + powf(ray.direction.z, 2);
	data.b = 2.0 * (ray.origin.x * ray.direction.x
			+ ray.origin.z * ray.direction.z);
	data.c = powf(ray.origin.x, 2) + powf(ray.origin.z, 2) - 1;
	if (!quadratic_equation_solution(&data, t) || fabsf(data.a) < EPSILON)
		return (false);
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

bool	intersec_sphere(t_shape *shape, t_list **inter)
{
	t_tuple	sphere_to_ray;
	t_tuple	origin;
	t_abcd	data;
	float	t[2];

	origin = ft_create_point(0, 0, 0);
	sphere_to_ray = substract_tuples(shape->ray_in_obj_space.origin, origin);
	data.a = dot_product(shape->ray_in_obj_space.direction,
			shape->ray_in_obj_space.direction);
	data.b = 2 * dot_product(shape->ray_in_obj_space.direction, sphere_to_ray);
	data.c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	data.discriminant = pow(data.b, 2) - 4 * data.a * data.c;
	if (!quadratic_equation_solution(&data, t))
		return (false);
	if (t[0] >= EPSILON)
		update_inter(inter, shape, t[0]);
	if (t[1] >= EPSILON)
		update_inter(inter, shape, t[1]);
	return (true);
}

void	identify_hit(t_list *xs_list)
{
	float	reference;
	t_xs	*aux;
	t_xs	*mark;

	reference = 214748368;
	aux = NULL;
	mark = NULL;
	while (xs_list != NULL)
	{
		aux = (t_xs *)xs_list->content;
		if (aux->time < reference && aux->time > 0)
		{
			reference = aux->time;
			if (mark)
				mark->hit = 0;
			aux->hit = 1;
			mark = aux;
		}
		xs_list = xs_list->next;
	}
}
