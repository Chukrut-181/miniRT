#include "../include/minirt.h"

t_4x4	ft_orientation(t_tuple left, t_tuple true_up, t_tuple forward)
{
	t_4x4	matrix;

	matrix = ft_create_identity_matrix();
	matrix.data[0][0] = left.x;
	matrix.data[0][1] = left.y;
	matrix.data[0][2] = left.z;

	matrix.data[1][0] = true_up.x;
	matrix.data[1][1] = true_up.y;
	matrix.data[1][2] = true_up.z;

	matrix.data[2][0] = forward.x;
	matrix.data[2][1] = forward.y;
	matrix.data[2][2] = forward.z;
	return (matrix);
}

t_4x4 view_transform(t_tuple origin, t_tuple direction)
{
	t_tuple forward, left, true_up, up;
	t_4x4 orientation;
	t_4x4 translation;
	float z;
	
	forward = ft_normalize(direction);
	up = ft_create_vector(0, 1, 0);
	if (fabsf(forward.y) > 0.9999f)
	{
		// Si miramos hacia arriba o abajo, usar otro vector como referencia
		if (forward.y > 0)
			z = -1;
		else
			z = 1;
		up = ft_create_vector(0, 0, z);
	}
	left = ft_normalize(ft_cross_product(forward, up));
	true_up = ft_cross_product(left, forward);
	orientation = ft_create_identity_matrix();
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	orientation.data[2][0] = -forward.x;
	orientation.data[2][1] = -forward.y;
	orientation.data[2][2] = -forward.z;
	translation = create_translation_mx(-origin.x, -origin.y, -origin.z);
	return (ft_multiply_matrices(orientation, translation));
}

static	void camera_guie(t_scene *scene, char *pov)
{
	float fov;
	float half_view;
	float aspect;

	fov = ft_atof(pov) * M_PI / 180.0; // Convertir de grados a radianes
	scene->camera->field_of_view = fov;
	scene->camera->hsize = WIDTH;
	scene->camera->vsize = HEIGHT;
	half_view = tanf(fov / 2);
	aspect = ((float)HEIGHT / WIDTH);
	if (aspect >= 1)
	{
		scene->camera->half_width = half_view;
		scene->camera->half_height = half_view / aspect;
	}
	else
	{
		scene->camera->half_width = half_view * aspect;
		scene->camera->half_height = half_view;
	}
	scene->camera->pixel_size = (scene->camera->half_width * 2) / scene->camera->hsize;
}

int ft_create_camera(t_scene *scene, char **cam_data)
{
	t_tuple	origin;
	t_tuple	direction;
	char	**coords;

	if (scene->camera != NULL)
		return (1);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (1);
	// Parsear la posicion de la camara
	if (!ft_check_coords(cam_data[1]))
		return (free(scene->camera), 1);
	coords = ft_split(cam_data[1], ',');
	origin = ft_create_point(ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2]));
	scene->camera->origin = origin;
	ft_free_array(coords);
	// Parsear el vector de orientacion
	if (!ft_check_coords(cam_data[2]))
		return (free(scene->camera), 1);
	coords = ft_split(cam_data[2], ',');
	direction = ft_create_vector(ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2]));
	direction = ft_normalize(direction);
	ft_free_array(coords);
	scene->camera->transform = view_transform(origin, direction);
	// Configurar el campo de visión y calcular parámetros de la cámara
	camera_guie(scene, cam_data[3]);
	return (0);
}

/* bool	ft_aim_camera(t_camera *cam1, float fov, char *point_of_view, char *orientation_vector)
{
	t_tuple		direction;
	char		**aux;

	cam1->hsize = WIDTH;
	cam1->vsize = HEIGHT;
	cam1->field_of_view = fov;
	if (!ft_check_coords(orientation_vector) || !ft_check_coords(point_of_view))
		return (free(cam1), false);
	aux = ft_split(point_of_view, ',');
	cam1->origin = ft_create_point(ft_atof(aux[0]), ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	aux = ft_split(orientation_vector, ',');
	direction = ft_create_vector(ft_atof(aux[0]), ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	cam1->transform = view_transform(cam1->origin, direction);
	return (true);
} */