#include "../include/minirt.h"

static t_list *ft_insert_sorted(t_list *sorted, t_xs *xs);

t_world ft_default_world(void)
{
	t_world world;
	t_sphere *s1, *s2;
	
	world.light = point_light(ft_create_point(-500, 500, -1000), ft_create_point(1, 1, 1));
	
	s1 = ft_create_sphere(ft_create_point(0, 0, 0), 1.0);
	s1->material.color = ft_create_point(0.8, 1.0, 0.6);
	s1->material.diffuse = 0.7;
	s1->material.specular = 0.2;

	s2 = ft_create_sphere(ft_create_point(0, 0, 0), 0.5);
	world.objects = NULL;
	ft_lstadd_back(&world.objects, ft_lstnew(s1));
	ft_lstadd_back(&world.objects, ft_lstnew(s2));
	return (world);
}

t_list *ft_intersect_world(t_world world, t_ray ray)
{
	t_list *intersections = NULL;
	t_list *current;
	t_sphere *sphere;
	
	current = world.objects;
	while (current)
	{
		sphere = (t_sphere *)current->content;
		intersections = ft_intersection(ray, *sphere, intersections);
		current = current->next;
	}
	intersections = ft_sort_intersections(intersections);
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

t_tuple	shade_hit(t_world world, t_comps comps)
{
	t_tuple	result;

	result = lighting(((t_sphere *)comps.object)->material, world.light, comps.point, comps.eyev, comps.normalv);
	return (result);
}

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
	shade = shade_hit(world, comps);
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

