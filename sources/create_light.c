/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:51:55 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/15 15:30:03 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static bool	ft_apply_light_coords(t_scene *scene, char *coords)
{
	char	**split;
	float	aux;
	int		i;

	split = ft_split(coords, ',');
	if (!split)
		return (false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]);
		if (i == 0)
			scene->world->light->source.x = aux;
		else if (i == 1)
			scene->world->light->source.y = aux;
		else if (i == 2)
			scene->world->light->source.z = aux;
		i++;
	}
	scene->world->light->source.w = 1;
	ft_free_array(split);
	return (true);
}

bool	ft_check_coords(char *coords)
{
	char	**temp;
	int		i;
	int		j;
	bool	checker;

	temp = ft_split(coords, ',');
	if (ft_arraylen(temp) != 3)
		return (ft_free_array(temp), false);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		checker = 0;
		while (temp[i][++j])
		{
			if ((temp[i][j] == '-' && j != 0)
				|| (temp[i][j] == '.' && checker == 1)
				|| (!ft_isdigit(temp[i][j]) && j != 0
				&& (temp[i][j] != '.')))
				return (ft_free_array(temp), false);
			if (temp[i][j] == '.')
				checker = 1;
		}
	}
	return (ft_free_array(temp), true);
}

bool	ft_create_light(t_scene *scene, char **light)
{
	float	aux;

	if (scene->world->light != NULL)
		ft_error_exit(scene, "Error\nDuplicated light", 1);
	scene->world->light = malloc(sizeof(t_light));
	if (scene->world->light == NULL)
		return (false);
	if (!ft_check_coords(light[1]))
		return (false);
	if (!ft_apply_light_coords(scene, light[1]))
		return (false);
	aux = ft_atof(light[2]);
	if (aux < 0 || 1 < aux)
		return (false);
	scene->world->light->intensity = aux;
	if (!ft_check_rgb(light[3]))
		return (false);
	if (!ft_apply_rgb(&scene->world->light->l_color, light[3]))
		return (false);
	return (true);
}
