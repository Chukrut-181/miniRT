#include "../include/minirt.h"

// esta bien
t_tuple	normal_at_plane(t_plane plane, t_tuple world_point)
{
	t_tuple	world_normal;
	t_4x4	inverse_transform;
	t_4x4	transpose_inverse;

	// para el plano la normal es constante
	if (plane.transform)
	{
		(void)world_point;
		inverse_transform = ft_find_inverse(*plane.transform);
		transpose_inverse = ft_transpose(inverse_transform);
		world_normal = ft_multiply_mat_and_tuple(transpose_inverse, plane.n_n_vector);
		world_normal.w = 0;
	}
	// no estoy seguro de que esto sea necesario, porque creo que siempre va a entrar en el if
	else
		world_normal = plane.n_n_vector;
	return (ft_normalize(world_normal));
}

t_xs intersect(t_plane *plane, t_ray *ray)
{
	t_xs intersection;
	t_ray transformed_ray;
	float denom;
	float t;
	t_4x4 inverse_transform;
	t_tuple normalized_normal;

	// inicializa a los valores default, ns si es realmente necesario
	intersection.hit = 0;
	intersection.time = 0;
	intersection.object = "plane";

	// normalizo el vector pero ya esta normalizado en el parseo, esto no hace falta pero el valor no cambia por mucho que normalizes algo que ya esta normalizado
	normalized_normal = ft_normalize(plane->n_n_vector);

	// si el plano tiene tranformacion, aplico la inversa del rayo, creo que esto cambiara si hacermos la matriz maestra en el parseo.
	if (plane->transform)
	{
		inverse_transform = ft_find_inverse(*plane->transform);
		transformed_ray.origin = ft_multiply_mat_and_tuple(inverse_transform, ray->origin);
		transformed_ray.direction = ft_multiply_mat_and_tuple(inverse_transform, ray->direction);
	}
	else
	{
		transformed_ray = *ray;
	}

	// chequear si el rayo el paralelo al plano
	denom = ft_dot_product(normalized_normal, transformed_ray.direction);
	if (fabsf(denom) < EPSILON)
		return (intersection);

	t = ft_dot_product(ft_substract_tuples(plane->point_in_plane, 
		transformed_ray.origin), normalized_normal) / denom;

	// si es negativo la inteseccion esta detras del origen del rayo
	if (t < 0)
		return (intersection);

	intersection.time = t;
	intersection.hit = 1;
	intersection.point = ft_position(transformed_ray, t);

	return (intersection);
}
//
//t_list	*intersect_plane(t_ray ray, t_plane plane, t_list *xs_list)
//{
//	t_xs	*intersection;
//	float	denom;
//	float	t;
//	t_ray	transformed_ray;
//	t_4x4	inverse_transform;
//
//	// si el plano tiene transformacion, aplicar la inversa del rayo
//	if (plane.transform)
//	{
//		inverse_transform = ft_find_inverse(*plane.transform);
//		transformed_ray.origin = ft_multiply_mat_and_tuple(inverse_transform, ray.origin);
//		transformed_ray.direction = ft_multiply_mat_and_tuple(inverse_transform, ray.direction);
//	}
//	else
//		transformed_ray = ray;
//	// chequea si el rayo es paralelo al plano
//	denom = ft_dot_product(plane.n_n_vector, transformed_ray.direction);
//	if (fabsf(denom) < EPSILON)
//		return (xs_list);
//
//	t = ft_dot_product(ft_substract_tuples(plane.point_in_plane, 
//		transformed_ray.origin), plane.n_n_vector) / denom;
//	// si la t es negativa la interseccion esta por detras del origen del rayo
//	if (t < 0)
//		return (xs_list);
//	intersection = malloc(sizeof(t_xs));
//	if (!intersection)
//		return (xs_list);
//
//	intersection->object = "plane";
//	intersection->time = t;
//	intersection->point = ft_position(transformed_ray, t);
//	intersection->hit = 0;
//
//	ft_lstadd_back(&xs_list, ft_lstnew(intersection));
//	ft_identify_hit(xs_list);
//	
//	return (xs_list);
//}
//
