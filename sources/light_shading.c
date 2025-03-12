#include "../include/minirt.h"

// testear estas dos funciones (eliminar estor posteriormente)

t_tuple	*normal_at(t_sphere *sphere, t_tuple *world_point)
{
	t_tuple *object_point;
	t_tuple *object_normal;
	t_tuple *world_normal;
	t_4x4	*inverse_sphere;

	inverse_sphere = ft_find_inverse(sphere.transform);
	object_point = ft_cross_product(inverse_sphere, world_point);
	object_normal = ft_substract_tuples(object_point, ft_create_point(0, 0, 0));
	world_normal = ft_transpose(ft_cross_product(inverse_sphere, object_normal));
	world_normal.w = 0;
	return (ft_normalize(world_normal));
}

t_tuple	*reflect(t_tuple *in, t_tuple *normal)
{
	
}
