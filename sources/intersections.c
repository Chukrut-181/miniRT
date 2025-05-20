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
	intersec.time = -1 * shape->ray_in_obj_space.origin.y / shape->ray_in_obj_space.direction.y;
	if (intersec.time > EPSILON)
	update_inter(inter, shape, intersec.time);
	else
	return (false);
	return (true);
}
static void	ft_intersect_caps(t_shape *cy_shape, t_ray ray, t_list **intersections)
{
	float t;
	t_tuple p;

	// Intersect with the bottom cap (y = 0 in object space)
	if (fabsf(ray.direction.y) < EPSILON)
		return;

	t = -ray.origin.y / ray.direction.y;
	if (t >= 0)
	{
		p = ft_add_tuples(ray.origin, ft_multiply_tuple_f(ray.direction, t));
		if (powf(p.x, 2) + powf(p.z, 2) <= 1) // Radius is 1 in object space
			update_inter(intersections, cy_shape, t);
	}

	// Intersect with the top cap (y = 1 in object space)
	t = (1 - ray.origin.y) / ray.direction.y; // Height is 1 in object space
	if (t >= 0)
	{
		p = ft_add_tuples(ray.origin, ft_multiply_tuple_f(ray.direction, t));
		if (powf(p.x, 2) + powf(p.z, 2) <= 1) // Radius is 1 in object space
			update_inter(intersections, cy_shape, t);
	}
}

bool    intersec_cylinder(t_shape *shape, t_list **inter, t_ray ray)
{
	t_tuple oc;
	float   a, b, c, discriminant;
	float   t0, t1;
	float   y0, y1;

	oc = ft_create_vector(ray.origin.x, ray.origin.y, ray.origin.z); // Origin in object space
	t_tuple direction = ft_create_vector(ray.direction.x, ray.direction.y, ray.direction.z); // Direction in object space

	a = powf(direction.x, 2) + powf(direction.z, 2);

	if (fabsf(a) < EPSILON) // Ray is parallel to the cylinder's axis (y-axis in object space)
	{
		return (ft_intersect_caps(shape, ray, inter), false);
	}

	b = 2.0 * (oc.x * direction.x + oc.z * direction.z);
	c = powf(oc.x, 2) + powf(oc.z, 2) - 1; // Radius is 1 in object space after scaling

	discriminant = b * b - 4.0 * a * c;

	 if (discriminant < 0)
		 return (ft_intersect_caps(shape, ray, inter), false); // Check caps even if no side intersection

	t0 = (-b - sqrtf(discriminant)) / (2.0 * a);
	t1 = (-b + sqrtf(discriminant)) / (2.0 * a);

	if (t0 > t1)
	{
		float temp = t0;
		t0 = t1;
		t1 = temp;
	}

	y0 = ray.origin.y + t0 * ray.direction.y;
	if (t0 > EPSILON && y0 >= 0 && y0 <= 1) // Height is 1 in object space after scaling
		update_inter(inter, shape, t0);

	y1 = ray.origin.y + t1 * ray.direction.y;
	if (t1 > EPSILON && y1 >= 0 && y1 <= 1) // Height is 1 in object space after scaling
		update_inter(inter, shape, t1);

	ft_intersect_caps(shape, ray, inter); // Always check for cap intersections

	return (*inter != NULL);
}

bool	intersec_sphere(t_shape *shape, t_list **inter)
{
	t_tuple	sphere_to_ray;
	t_tuple origin;
	float	a, b, c, discriminant;
	float	t1;
	float	t2;

	origin = ft_create_point(0, 0, 0);
	sphere_to_ray = ft_substract_tuples(shape->ray_in_obj_space.origin, origin);
	a = ft_dot_product(shape->ray_in_obj_space.direction, shape->ray_in_obj_space.direction);
	b = 2 * ft_dot_product(shape->ray_in_obj_space.direction, sphere_to_ray);
	c = ft_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t1 = (-b - sqrtf(discriminant)) / (2 * a);
	t2 = (-b + sqrtf(discriminant)) / (2 * a);
	if (t1 < EPSILON || t2 < EPSILON)
		return (false);
	update_inter(inter, shape, t2);
	update_inter(inter, shape, t1);
	return (true);
}

void	ft_identify_hit(t_list *xs_list)
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
/*
static void	ft_calculate_abcd(t_ray ray, t_sphere sphere, t_abcd *data)
{
	t_tuple	sphere_to_ray;

	sphere_to_ray = ft_substract_tuples(ray.origin, sphere.center);
	data->a = ft_dot_product(ray.direction, ray.direction);
	data->b = 2 * ft_dot_product(ray.direction, sphere_to_ray);
	data->c = (ft_dot_product(sphere_to_ray, sphere_to_ray)
			- (sphere.diameter/2 * sphere.diameter/2));
	data->discriminant = (data->b * data->b) - (4 * data->a * data->c);
	return ;
}*/
