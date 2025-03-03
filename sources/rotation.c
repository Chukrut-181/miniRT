#include "../include/minirt.h"

t_4x4	*rotation_x_mx(double radians)
{
	t_4x4	*rotation_x_mx;

	rotation_x_mx = ft_create_identity_matrix();
	rotation_x_mx->data[1][1] = cos(radians);
	rotation_x_mx->data[1][2] = -sin(radians);
	rotation_x_mx->data[2][1] = sin(radians);
	rotation_x_mx->data[2][2] = cos(radians);
	return (rotation_x_mx);
}

t_4x4	*rotation_y_mx(double radians)
{
	t_4x4	*rotation_y_mx;

	rotation_y_mx = ft_create_identity_matrix();
	rotation_y_mx->data[0][0] = cos(radians);
	rotation_y_mx->data[0][2] = sin(radians);
	rotation_y_mx->data[2][0] = -sin(radians);
	rotation_y_mx->data[2][2] = cos(radians);
	return (rotation_y_mx);
}

t_4x4	*rotation_z_mx(double radians)
{
	t_4x4	*rotation_z_mx;

	rotation_z_mx = ft_create_identity_matrix();
	rotation_z_mx->data[0][0] = cos(radians);
	rotation_z_mx->data[0][1] = -sin(radians);
	rotation_z_mx->data[1][0] = sin(radians);
	rotation_z_mx->data[1][1] = cos(radians);
	return (rotation_z_mx);
}
