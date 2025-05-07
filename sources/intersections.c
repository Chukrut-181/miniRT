/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:59:10 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/07 14:22:00 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static	void	update_plane_inter(t_list **inter, t_shape *shape, float time)
{
	t_xs	*intersec;

	intersec = malloc(sizeof(t_xs));
	if (!intersec)
		return ;
	intersec->object = shape;
	intersec->time = time;
	intersec->hit = 1;
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
		update_plane_inter(inter, shape, intersec.time);
	else
		return (false);
	return (true);
}

static void	update_sphere_inter(float time, t_shape *shape, t_list **inter)
{
	t_xs	*intersec;

	intersec = malloc(sizeof(t_xs));
	if (!intersec)
		return ;
	intersec->object = shape;
	intersec->time = time;
	intersec->hit = 1;
	if (*inter == NULL)
		*inter = ft_lstnew(intersec);
	else
		ft_lstadd_back(inter, ft_lstnew(intersec));
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
	update_sphere_inter(t2, shape, inter);
    update_sphere_inter(t1, shape, inter);
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
}

t_list	*ft_register_intersections(t_abcd data, t_list *xs_list, t_ray ray)
{
	t_xs	*first_xs;
	t_xs	*second_xs;

	first_xs = malloc(sizeof(t_xs));
	first_xs->object = SPHERE;
	first_xs->time = (-data.b - sqrtf(data.discriminant)) / (2 * data.a);
	first_xs->point = ft_position(ray, first_xs->time);
	first_xs->hit = 0;
	second_xs = malloc(sizeof(t_xs));
	second_xs->object = SPHERE;
	second_xs->time = (-data.b + sqrtf(data.discriminant)) / (2 * data.a);
	second_xs->point = ft_position(ray, first_xs->time);
	second_xs->hit = 0;
	ft_lstadd_back(&xs_list, ft_lstnew(first_xs));
	ft_lstadd_back(&xs_list, ft_lstnew(second_xs));
	return (xs_list);
}

t_list	*ft_intersection_sphere(t_ray ray, t_sphere sphere, t_list *xs_list)
{
	t_abcd	solution_data;

	ft_calculate_abcd(ray, sphere, &solution_data);
	if (solution_data.discriminant < 0)
		return (NULL);
	xs_list = ft_register_intersections(solution_data, xs_list, ray);
	ft_identify_hit(xs_list);
	return (xs_list);
}
 */
