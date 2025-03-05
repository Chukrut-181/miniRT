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
