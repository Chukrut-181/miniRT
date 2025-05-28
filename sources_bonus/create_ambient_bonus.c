/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ambient_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:18:17 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/28 11:33:36 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	apply_rgb(t_color *color, char *original)
{
	char	**split;
	float	aux;
	int		i;

	split = ft_split(original, ',');
	if (!split)
		return (false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]) / 255.0;
		if (aux < 0 || 1 < aux)
			return (free(split), false);
		if (i == 0)
			color->r = aux;
		else if (i == 1)
			color->g = aux;
		else if (i == 2)
			color->b = aux;
		i++;
	}
	return (free(split), true);
}

bool	check_rgb(char *colorcode)
{
	char	**split;
	int		i;
	int		j;

	split = ft_split(colorcode, ',');
	if (ft_arraylen(split) > 3)
		return (ft_free_array(split), false);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (split[i][j] && split[i][j] != '\n')
		{
			if (!ft_isdigit(split[i][j]))
				return (ft_free_array(split), false);
			else
				j++;
		}
		i++;
	}
	ft_free_array(split);
	return (true);
}

bool	create_ambient(t_world *world, char **ambient)
{
	float	aux;

	if (world->ambient != NULL || ft_arraylen(ambient) != 3)
		return (false);
	world->ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (world->ambient == NULL)
		return (false);
	aux = ft_atof(ambient[1]);
	if (aux < 0 || 1 < aux)
		return (free(world->ambient), false);
	world->ambient->ratio = aux;
	if (!check_rgb(ambient[2]))
		return (free(world->ambient), false);
	if (!apply_rgb(&world->ambient->a_color, ambient[2]))
		return (free(world->ambient), false);
	return (true);
}
