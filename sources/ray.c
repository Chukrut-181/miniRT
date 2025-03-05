#include "../include/minirt.h"

t_ray	ft_create(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple	ft_position(t_ray ray, int t)
{
	t_tuple point;

	point = ft_multiply_tuple(point, t);
	point = ft_add_tuples(ray.origin, ray.direction);
	return (point);
}

t_sphere *ft_create_sphere()
{
	t_sphere *sphere;
	
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = *ft_create_point(0, 0, 0);
	sphere->radius = 1.0;
	sphere->transform = ft_create_identity_matrix();
	sphere->inverse_transform = ft_create_identity_matrix();
	return (sphere);
}

t_intersections *ft_intersecting_ray_sphere(t_shpere *s, t_ray ray)
{
	t_tuple	sphere_to_ray;
	t_ray	transformed_ray;
	float	a, b, c, discriminant;
	t_intersections *inter;

	inter = malloc(sizeof(t_intersections));

	transformed_ray.origin = ft_multiply_mat_and_tuple(s->inverse_transform, &ray.origin);
	transformed_ray.direction = ft_multiply_mat_and_tuple(s->inverse_transform, &ray.direction);

	shpere_to_ray = ft_substract_tuples(&transformed_ray.origin, &sphere->center);

	a = ft_dot_product(&transformed_ray.direction, &transformed_ray.direction);
	b = 2 * ft_dot_product(&transformed_ray.direction, &sphere_to_ray);
	c = ft_dot_product(&sphere_to_ray, &sphere_to_ray) - 1;

	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		inter->count = 0;
		inter->intersections = NULL;
		return (inter);
	}
	
	inter->count = 2;
	inter->intersections = malloc(sizeof(t_intersection) * 2);

	inter->intersections[0].t = (-b - sqrt(discriminant)) / (2 * a);
	inter->intersections[1].t = (-b - sqrt(discriminant)) / (2 * a);
	inter->intersections[0].object = sphere;
	inter->intersections[1].object = sphere;
	return (inter);
}

