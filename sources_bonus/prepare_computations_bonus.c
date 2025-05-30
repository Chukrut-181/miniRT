#include "../include/minirt_bonus.h"

static bool	object_in_containers(t_list *containers, t_shape *object)
{
	t_list	*current;

	current = containers;
	while (current)
	{
		if ((t_shape *)current->content == object)
			return (true);
		current = current->next;
	}
	return (false);
}

static void	remove_object_from_containers(t_list **containers, t_shape *object)
{
	t_list	*current;
	t_list	*prev;

	current = *containers;
	prev = NULL;
	while (current)
	{
		if ((t_shape *)current->content == object)
		{
			if (prev)
				prev->next = current->next;
			else
				*containers = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static float	get_last_refractive_index(t_list *containers)
{
	t_list	*current;
	t_shape	*last_object;

	if (!containers)
		return (1.0);
	current = containers;
	while (current->next)
		current = current->next;
	last_object = (t_shape *)current->content;
	return (last_object->material.refractive_index);
}

static void	calculate_refractive_indices(t_xs *hit, t_list *xs, t_comps *comps)
{
	t_list	*containers;
	t_list	*current_xs;
	t_xs	*intersection;

	containers = NULL;
	current_xs = xs;
	while (current_xs)
	{
		intersection = (t_xs *)current_xs->content;
		if (intersection == hit)
			comps->n1 = get_last_refractive_index(containers);
		if (object_in_containers(containers, intersection->object))
			remove_object_from_containers(&containers, intersection->object);
		else
			ft_lstadd_back(&containers, ft_lstnew(intersection->object));
		if (intersection == hit)
		{
			comps->n2 = get_last_refractive_index(containers);
			break;
		}
		current_xs = current_xs->next;
	}
}

t_comps	prepare_computations(t_xs *hit, t_ray ray, t_list *xs)
{
	t_comps	comps;

	comps.time = hit->time;
	comps.object = hit->object;
	comps.point = ft_position(ray, comps.time);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at((t_shape *)comps.object, comps.point);
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = false;
    comps.over_point = add_tuples(comps.point, multiply_tuple_f(comps.normalv, EPSILON));
	comps.reflectv = reflect(ray.direction, comps.normalv);
    comps.under_point = substract_tuples(comps.point, multiply_tuple_f(comps.normalv, EPSILON));
	if (xs)
		calculate_refractive_indices(hit, xs, &comps);
	else
	{
		comps.n1 = 1.0;
		comps.n2 = 1.0;
	}
	return (comps);
}
