#include "../include/minirt.h"

//static void	ft_print_4x4(t_4x4 *matrix)
//{
//	int i = 0; //	int j; //
//	while (i < 4)
//	{
//		j = 0;
//		while (j < 4)
//		{
//			printf("%f ", matrix->data[i][j]);
//			j++;
//		}
//		printf("\n");
//		i++;
//	}
//}
//
static t_4x4	*ft_create_identity_matrix()
{
	t_4x4	*matrix = malloc(sizeof(t_4x4) * 1);

	matrix->data[0][0] = 1.0;
	matrix->data[0][1] = 0.0;
	matrix->data[0][2] = 0.0;
	matrix->data[0][3] = 0.0;
	matrix->data[1][0] = 0.0;
	matrix->data[1][1] = 1.0;
	matrix->data[1][2] = 0.0;
	matrix->data[1][3] = 0.0;
	matrix->data[2][0] = 0.0;
	matrix->data[2][1] = 0.0;
	matrix->data[2][2] = 1.0;
	matrix->data[2][3] = 0.0;
	matrix->data[3][0] = 0.0;
	matrix->data[3][1] = 0.0;
	matrix->data[3][2] = 0.0;
	matrix->data[3][3] = 1.0;
	return (matrix);
}

t_4x4	*translation(t_tuple *tuple)
{
	t_4x4	*identity_matrix;

	identity_matrix = ft_create_identity_matrix();
	identity_matrix->data[0][3] = tuple->x;
	identity_matrix->data[1][3] = tuple->y;
	identity_matrix->data[2][3] = tuple->z;
	return (identity_matrix);
}

t_4x4	*scaling(t_tuple *tuple)
{
	t_4x4	*identity_matrix;

	identity_matrix = ft_create_identity_matrix();
	identity_matrix->data[0][0] = tuple->x;
	identity_matrix->data[1][1] = tuple->y;
	identity_matrix->data[2][2] = tuple->z;
	return (identity_matrix);
}
