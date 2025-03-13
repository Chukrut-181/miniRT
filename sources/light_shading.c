#include "../include/minirt.h"

// testear todas estas funciones (eliminar estor posteriormente)

t_material	ft_create_material(float x, float y, float z)
{
	t_material m;

	m.color = ft_create_point(x, y, z);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	return (m);
}

t_tuple	normal_at(t_sphere sphere, t_tuple world_point)
{
	t_tuple	object_normal;
	t_tuple	world_normal;

	object_normal = ft_substract_tuples(world_point, sphere.center);
	world_normal = ft_normalize(object_normal);
	world_normal.w = 0;
	return (world_normal);
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	float	dop;
	t_tuple	scaled;
	t_tuple	result;

	dop = ft_dot_product(in, normal);
	scaled = ft_multiply_tuple(normal, 2.0 * dop);
	result = ft_substract_tuples(in, scaled);
	return (result);
}

t_light	point_light(t_tuple position, t_tuple intensity)
{
	t_light light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

t_tuple	lighting(t_material mat, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
	t_tuple	effective_color;
	t_tuple	lightv;
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
	t_tuple	reflectv;
	t_tuple	res;
	float	light_dot_normal;
	float	reflect_dot_eye = 0.0;
	float	factor;

	effective_color = ft_multiply_colors(mat.color, light.intensity);
	lightv = ft_substract_tuples(light.position, point);
	lightv = ft_normalize(lightv);
	ambient = ft_multiply_tuple(effective_color, mat.ambient);
	light_dot_normal = ft_dot_product(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = ft_create_point(0, 0, 0);
		specular = ft_create_point(0, 0, 0);
	}
	else
	{
		diffuse = ft_multiply_tuple(effective_color, mat.diffuse * light_dot_normal);
		reflectv = reflect(ft_negate_tuple(lightv), normalv);
		reflect_dot_eye = ft_dot_product(reflectv, eyev);
	}
	if (reflect_dot_eye <= 0)
		specular = ft_create_point(0, 0, 0);
	else
	{
		factor = powf(reflect_dot_eye, mat.shininess);
		specular = ft_multiply_tuple(light.intensity, (mat.specular * factor));
	}
	res = ft_add_tuples(ambient, ft_add_tuples(diffuse, specular));
	return (res);
}

void test_lighting() {
		// Create a material
		t_material m = ft_create_material(1, 1, 1); // White material

		// Create a position
		t_tuple position = ft_create_point(0, 0, 0);

		// Test case 1: Eye between light and surface, normal same as eye direction
		{
				t_tuple eyev = ft_create_vector(0, 0, -1);
				t_tuple normalv = ft_create_vector(0, 0, -1);
				t_light light = point_light(ft_create_point(0, 0, -10), ft_create_point(1, 1, 1));

				t_tuple result = lighting(m, light, position, eyev, normalv);
				printf("Test 1 - Eye between light and surface:\n");
				printf("  Result: RGB(%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
				printf("  Expected: RGB close to (1.9, 1.9, 1.9)\n\n");
		}

		// Test case 2: Eye offset 45 degrees, normal straight on
		{
				t_tuple eyev = ft_create_vector(0, sqrt(2)/2, -sqrt(2)/2);
				t_tuple normalv = ft_create_vector(0, 0, -1);
				t_light light = point_light(ft_create_point(0, 0, -10), ft_create_point(1, 1, 1));

				t_tuple result = lighting(m, light, position, eyev, normalv);
				printf("Test 2 - Eye offset 45 degrees:\n");
				printf("  Result: RGB(%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
				printf("  Expected: RGB close to (1.0, 1.0, 1.0)\n\n");
		}

		// Test case 3: Light offset 45 degrees, eye straight on
		{
				t_tuple eyev = ft_create_vector(0, 0, -1);
				t_tuple normalv = ft_create_vector(0, 0, -1);
				t_light light = point_light(ft_create_point(0, 10, -10), ft_create_point(1, 1, 1));

				t_tuple result = lighting(m, light, position, eyev, normalv);
				printf("Test 3 - Light offset 45 degrees:\n");
				printf("  Result: RGB(%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
				printf("  Expected: RGB close to (0.7, 0.7, 0.7)\n\n");
		}

		// Test case 4: Eye in the path of the reflection vector
		{
				t_tuple eyev = ft_create_vector(0, -sqrt(2)/2, -sqrt(2)/2);
				t_tuple normalv = ft_create_vector(0, 0, -1);
				t_light light = point_light(ft_create_point(0, 10, -10), ft_create_point(1, 1, 1));

				t_tuple result = lighting(m, light, position, eyev, normalv);
				printf("Test 4 - Eye in reflection path:\n");
				printf("  Result: RGB(%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
				printf("  Expected: RGB close to (1.6, 1.6, 1.6)\n\n");
		}

		// Test case 5: Light behind the surface
		{
				t_tuple eyev = ft_create_vector(0, 0, -1);
				t_tuple normalv = ft_create_vector(0, 0, -1);
				t_light light = point_light(ft_create_point(0, 0, 10), ft_create_point(1, 1, 1));

				t_tuple result = lighting(m, light, position, eyev, normalv);
				printf("Test 5 - Light behind surface:\n");
				printf("  Result: RGB(%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
				printf("  Expected: RGB(0.1, 0.1, 0.1) (ambient only)\n");
		}
}

// Test function for reflection
void test_reflection() {
	// Test case: Reflecting a vector approaching at 45°
	t_tuple v = ft_create_vector(1, -1, 0);
	t_tuple n = ft_create_vector(0, 1, 0);
	t_tuple r = reflect(v, n);
	
	printf("\nTest reflection:\n");
	printf("  Vector: (%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
	printf("  Normal: (%.2f, %.2f, %.2f)\n", n.x, n.y, n.z);
	printf("  Reflected: (%.2f, %.2f, %.2f)\n", r.x, r.y, r.z);
	printf("  Expected: (1.00, 1.00, 0.00)\n");
}

void render_lit_sphere(mlx_image_t *image)
{
	t_sphere sphere;
	t_light light;
	t_tuple eye_pos;
	t_ray ray;
	t_list *xs_list;
	t_xs *intersection;
	t_tuple point;
	t_tuple normal;
	t_tuple eye_v;
	t_tuple color;
	int x, y;
	
	sphere.center = ft_create_point(0, 0, 0);
	sphere.radius = 500;
	sphere.material = ft_create_material(1, 0.2, 1);  // Purple/magenta color
	sphere.material.ambient = 0.1;
	sphere.material.diffuse = 0.7;
	sphere.material.specular = 0.3;
	sphere.material.shininess = 200.0;
	
	// Create a light source (positioned to create highlight in upper-right)
	light = point_light(ft_create_point(-500, 500, -1000), ft_create_point(1, 1, 1));
	// Eye position
	eye_pos = ft_create_point(0, 0, -1000);
	
	// Render the sphere with lighting
	y = 0;
	while(y < 1800)
	{
		x = 0;
		while(x < 2400)
		{
			// Create a ray from the eye through this pixel
			t_tuple pixel_point = ft_create_point(x - 1200, 900 - y, 0);
			t_tuple direction = ft_normalize(ft_substract_tuples(pixel_point, eye_pos));
			ray = ft_create_ray(eye_pos, direction);
			// Find intersections
			xs_list = ft_intersection(ray, sphere, NULL);
			// If we hit the sphere
			if (xs_list)
			{
				// Find the hit point (the closest intersection in front of the eye)
				intersection = NULL;
				while (xs_list)
				{
					t_xs *current = (t_xs *)xs_list->content;
					if (current->hit)
					{
						intersection = current;
						break;
					}
					xs_list = xs_list->next;
				}
				if (intersection)
				{
					// Calculate the actual point of intersection
					point = ft_position(ray, intersection->time);
					// Calculate the normal at the intersection point
					normal = normal_at(sphere, point);
					// Calculate the eye vector
					eye_v = ft_normalize(ft_negate_tuple(ray.direction));
					// Calculate the color using the lighting function
					color = lighting(sphere.material, light, point, eye_v, normal);
					// Convert color to uint32_t for MLX
					uint32_t pixel_color = ((uint32_t)(color.x * 255) << 24) | 
										 ((uint32_t)(color.y * 255) << 16) | 
										 ((uint32_t)(color.z * 255) << 8) | 
										 0xFF;
					mlx_put_pixel(image, x, y, pixel_color);
				}
				ft_lstclear(&xs_list, free);
			}
			x++;
		}
		y++;
	}
}

