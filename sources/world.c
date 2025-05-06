#include "../include/minirt.h"

static t_list *ft_insert_sorted(t_list *sorted, t_xs *xs);

static t_ray transform(t_ray ray, t_4x4	matrix)
{
	t_tuple	multi[2];
	t_tuple p;
	t_tuple vec;
	t_ray	new_ray;

	multi[0] = ft_multiply_mat_and_tuple(matrix, ray.origin);
	multi[1] = ft_multiply_mat_and_tuple(matrix, ray.direction);
	p = ft_create_point(multi[0].x, multi[0].y, multi[0].z);
	vec = ft_create_point(multi[1].x, multi[1].y, multi[1].z);
	new_ray.origin = p;
	new_ray.direction = vec;
	return (new_ray);
}

static	t_list	*ft_intersections(t_ray ray, t_shape *shape, t_list **inter)
{
	shape->ray_in_obj_space = transform(ray, *shape->inverse_matrix);
	if (shape->type == SPHERE)
		intersec_sphere(shape, inter);
	else if (shape->type == PLANE)
		intersec_plane(shape, inter);
//	else if (shape->type == CYLINDER)
//		intersec_cylinder(shape, inter);
	return (inter);
}

t_list *ft_intersect_world(t_world world, t_ray ray)
{
	t_list *intersections = NULL;
	t_list *current;
	t_shape *shape;

	current = world.objects;
	while (current)
	{
		shape = (t_shape *)current->content;
		intersections = ft_intersection(ray, shape, &intersections);
		current = current->next;
	}
	//intersections = ft_sort_intersections(intersections);
	return (intersections);
}

t_comps	prepare_computations(t_list *intersection, t_ray ray)
{
	t_comps	comps;
	t_xs	*hit = (t_xs *)intersection->content;

	comps.time = hit->time;
	comps.object = hit->object;
	comps.point = ft_position(ray, comps.time);
	comps.eyev = ft_negate_tuple(ray.direction);
	comps.normalv = normal_at(*(t_sphere *)comps.object, comps.point);
	if (ft_dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = ft_negate_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

//tuple	shade_hit(t_world world, t_comps comps)
//{
//	t_tuple	result;
//
//	result = lighting(((t_sphere *)comps.object)->material, world.light, comps.point, comps.eyev, comps.normalv);
//	return (result);
//}

t_list *ft_find_hit(t_list *intersections)
{
	t_list *current;
	t_list *hit;
	t_xs *xs;
	float min_time;
	
	current = intersections;
	hit = NULL;
	min_time = INFINITY;
	
	while (current)
	{
		xs = (t_xs *)current->content;
		
		if (xs->time > 0 && xs->time < min_time)
		{
			min_time = xs->time;
			hit = current;
		}
		
		current = current->next;
	}
	
	return (hit);
}

t_tuple	color_at(t_world world, t_ray ray)
{
	t_list	*intersect;
	t_list	*hit;
	t_comps	comps;
	t_tuple	shade;

	intersect = ft_intersect_world(world, ray);
	hit = ft_find_hit(intersect);
	if (hit == NULL)
	{
		shade = ft_create_point(0, 0, 0);
		t_list *current = intersect;
		while (current)
		{
			t_list *next = current->next;
			free(current->content);
			free(current);
			current = next;
		}
		return (shade);
	}
	comps = prepare_computations(intersect, ray);
	//shade = shade_hit(world, comps);
	t_list *current = intersect;
	while (current)
	{
		t_list *next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	return (shade);
}

t_list *ft_sort_intersections(t_list *intersections)
{
	t_list *sorted = NULL;
	t_list *current;
	t_list *temp;
	t_xs *xs;
	
	if (intersections == NULL || intersections->next == NULL)
		return (intersections);
	
	current = intersections;
	while (current)
	{
		xs = (t_xs *)current->content;
		sorted = ft_insert_sorted(sorted, xs);
		current = current->next;
	}
	current = intersections;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	
	return (sorted);
}

static t_list *ft_insert_sorted(t_list *sorted, t_xs *xs)
{
	t_list *new_node;
	t_list *current;
	t_list *prev;
	
	new_node = ft_lstnew(xs);
	if (sorted == NULL || ((t_xs *)sorted->content)->time > xs->time)
	{
		new_node->next = sorted;
		return (new_node);
	}
	current = sorted;
	prev = NULL;
	while (current && ((t_xs *)current->content)->time <= xs->time)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new_node;
	new_node->next = current;
	return (sorted);
}

