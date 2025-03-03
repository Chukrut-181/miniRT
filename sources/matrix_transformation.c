#include "../include/minirt.h"

t_4x4	*ft_create_identity_matrix(void)
{
	t_4x4	*idmatrix;
	int		i;
	int		j;

	idmatrix = malloc(sizeof(t_4x4));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				idmatrix->data[i][j] = 1;
			else
				idmatrix->data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (idmatrix);
}

t_4x4	*create_translation_mx(t_tuple *tuple)
{
	t_4x4	*translation_mx;

	translation_mx = ft_create_identity_matrix();
	translation_mx->data[0][3] = tuple->x;
	translation_mx->data[1][3] = tuple->y;
	translation_mx->data[2][3] = tuple->z;
	return (translation_mx);
}

t_4x4	*create_scalation_mx(t_tuple *tuple)
{
	t_4x4	*scalation_mx;

	scalation_mx = ft_create_identity_matrix();
	scalation_mx->data[0][0] = tuple->x;
	scalation_mx->data[1][1] = tuple->y;
	scalation_mx->data[2][2] = tuple->z;
	return (scalation_mx);
}
