#include "../include/minirt.h"

t_4x4	*rotation_x(double radians)
{
	t_4x4	*identity_matrix;

	identity_matrix = ft_create_identity_matrix();
	identity_matrix->data[1][1] = cos(radians);
	identity_matrix->data[1][2] = -sin(radians);
	identity_matrix->data[2][1] = sin(radians);
	identity_matrix->data[2][2] = cos(radians);
	return (identity_matrix);
}

t_4x4	*rotation_y(double radians)
{
	t_4x4	*identity_matrix;

	identity_matrix = ft_create_identity_matrix();
	identity_matrix->data[0][0] = cos(radians);
	identity_matrix->data[0][2] = sin(radians);
	identity_matrix->data[2][0] = -sin(radians);
	identity_matrix->data[2][2] = cos(radians);
	return (identity_matrix);
}

t_4x4	*rotation_z(double radians)
{
	t_4x4	*identity_matrix;

	identity_matrix = ft_create_identity_matrix();
	identity_matrix->data[0][0] = cos(radians);
	identity_matrix->data[0][1] = -sin(radians);
	identity_matrix->data[1][0] = sin(radians);
	identity_matrix->data[1][1] = cos(radians);
	return (identity_matrix);
}
