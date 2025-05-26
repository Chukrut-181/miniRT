/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:18:17 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/26 10:55:57 by igchurru         ###   ########.fr       */
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

bool	create_ambient(t_scene *scene, char **ambient)
{
	float	aux;

	if (scene->ambient != NULL)
		ft_error_exit(scene, "Error\nOnly one ambient light allowed", 1);
	scene->ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (scene->ambient == NULL)
		return (false);
	aux = ft_atof(ambient[1]);
	if (aux < 0 || 1 < aux)
		return (free(scene->ambient), false);
	scene->ambient->ratio = aux;
	if (!check_rgb(ambient[2]))
		return (free(scene->ambient), false);
	if (!apply_rgb(&scene->ambient->a_color, ambient[2]))
		return (free(scene->ambient), false);
	return (true);
}
