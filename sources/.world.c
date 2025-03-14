#include "../include/minirt.h"

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
	// Aqui deveriamos ordenar las interseciones.
	return (intersections);
}

t_comps	prepare_computations(t_list *intersection, t_ray ray)
{
	t_comps	comps;
	t_xs	*hit = (t_xs *)intersection->content;

	comps.time = hit->time;
	comps.object = hit->object;
	comps.point = ft_position(ray.direction);
	comps.eyev = ft_negate_tuple(ray.direction);
	comps.normalv = normal_at(*(t_sphere)comps.object, comps.point);
	return (comps);
}
