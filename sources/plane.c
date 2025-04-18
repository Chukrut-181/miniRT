#include "../include/minirt.h"

t_list *intersect_plane(t_ray ray, t_plane plane, t_list *xs_list)
{
	t_xs *intersection;
	t_xs result;
	
	result = intersect(&plane, &ray);
	if (result.hit)
	{
		intersection = malloc(sizeof(t_xs));
		if (!intersection)
			return (xs_list);
		*intersection = result;
		ft_lstadd_back(&xs_list, ft_lstnew(intersection));
	}
	if (xs_list)
		ft_identify_hit(xs_list);
	return (xs_list);
}

t_tuple normal_at_plane(t_plane plane, t_tuple point)
{
	t_tuple normal;
	t_4x4 inverse_transform;
	t_4x4 transpose_inverse;
	
	// For a plane, the normal is constant regardless of the point
	(void)point;
	normal = plane.n_n_vector;
	
	// If the plane has a transform, we need to transform the normal
	if (plane.transform)
	{
		inverse_transform = ft_find_inverse(*plane.transform);
		transpose_inverse = ft_transpose(inverse_transform);
		normal = ft_multiply_mat_and_tuple(transpose_inverse, normal);
		normal.w = 0; // Ensure it's a vector, not a point
	}
	
	// Always normalize the result
	return ft_normalize(normal);
}

t_xs intersect(t_plane *plane, t_ray *ray)
{
	t_xs xs;
	float dot;
	float t;
	t_ray object_ray;
	
	xs.object = NULL;
//	xs.time = -1;
//	xs.hit = 0;
	if (plane->transform)
	{
		object_ray = *ray;
		t_4x4 inverse_transform = ft_find_inverse(*plane->transform);
		object_ray.origin = ft_multiply_mat_and_tuple(inverse_transform, ray->origin);
		object_ray.direction = ft_multiply_mat_and_tuple(inverse_transform, ray->direction);
		ray = &object_ray;
	}
	dot = ft_dot_product(plane->n_n_vector, ray->direction);
	if (fabs(dot) < EPSILON)
		return (xs);
	t = ft_dot_product(ft_substract_tuples(plane->point_in_plane, ray->origin),plane->n_n_vector) / dot;
	if (t < 0)
		return (xs);
	xs.object = plane;
	xs.time = t;
	xs.point = ft_position(*ray, t);
	xs.hit = 1;
	return (xs);
}

void render_plane(t_scene *s)
{
	t_plane *plane;
	t_ray ray;
	t_xs intersection;
	t_tuple point;
	t_tuple normal;
	t_tuple eye_v;
	t_tuple color;
	int x, y;
	t_list *current;
	
	current = s->objects;
	plane = NULL;
	
	while (current)
	{
		if (*(t_type *)(current->content) == PLANE)
		{
			plane = (t_plane *)current->content;
			break;
		}
		current = current->next;
	}
	
	if (!plane)
	{
		printf("No plane found in the scene!\n");
		return;
	}

	for (y = HEIGHT / 2; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			// Create a ray from the eye through this pixel
			t_tuple pixel_point = ft_create_point(x - (WIDTH/2), (HEIGHT/2) - y, 0);
			t_tuple direction = ft_normalize(ft_substract_tuples(pixel_point, s->camera->viewpoint));
			ray = ft_create_ray(s->camera->viewpoint, direction);
			
			// Find intersection with the plane
			intersection = intersect(plane, &ray);
			
			// If we hit the plane
			if (intersection.hit)
			{
				// Calculate the actual point of intersection
				point = ft_position(ray, intersection.time);
				
				// Get the normal at the intersection point
				normal = normal_at_plane(*plane, point);
				
				// Calculate the eye vector
				eye_v = ft_normalize(ft_negate_tuple(ray.direction));
				
				// Calculate the color using the lighting function with the plane's material
				color = lighting(plane->material, *s->light, point, eye_v, normal);
				
				// Convert color to uint32_t for MLX
				uint32_t pixel_color = ((uint32_t)(color.x * 255) << 24) | 
									 ((uint32_t)(color.y * 255) << 16) | 
									 ((uint32_t)(color.z * 255) << 8) | 
									 0xFF;
				
				mlx_put_pixel(s->image, x, y, pixel_color);
			}
			else
			{
				// Set background color (dark blue)
				mlx_put_pixel(s->image, x, y, 0xFF000020);
			}
		}
	}
}

