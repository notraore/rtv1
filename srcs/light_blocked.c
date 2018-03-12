/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_blocked.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	blocked_by_a_cone(t_datas *d, int *light_blocked, t_object *object)
{
	t_cone	*tmp_cone;

	tmp_cone = object->start_cone;
	while (tmp_cone)
	{
		if (tmp_cone->id != d->id_cone)
		{
			if (cone_intersection(d, tmp_cone))
			{
				if (d->solution < d->distance_light_object && d->solution >= 0)
				{
					*light_blocked = 1;
					break ;
				}
			}
		}
		tmp_cone = tmp_cone->next;
	}
}

void	blocked_by_a_cylinder(t_datas *d, int *light_blocked, t_object *object)
{
	t_cylinder	*tmp_cylinder;

	tmp_cylinder = object->start_cylinder;
	while (tmp_cylinder)
	{
		if (tmp_cylinder->id != d->id_cylinder)
		{
			if (cylinder_intersection(d, tmp_cylinder))
			{
				if (d->solution < d->distance_light_object && d->solution >= 0)
				{
					*light_blocked = 1;
					break ;
				}
			}
		}
		tmp_cylinder = tmp_cylinder->next;
	}
}

void	blocked_by_a_sphere(t_datas *d, int *light_blocked, t_object *object)
{
	t_sphere	*tmp_sphere;

	tmp_sphere = object->start_sphere;
	while (tmp_sphere)
	{
		if (tmp_sphere->id != d->id_sphere)
		{
			if (sphere_intersection(d, tmp_sphere))
			{
				if (d->solution < d->distance_light_object && d->solution >= 0)
				{
					*light_blocked = 1;
					break ;
				}
			}
		}
		tmp_sphere = tmp_sphere->next;
	}
}

void	blocked_by_a_plane(t_datas *d, int *light_blocked, t_object *object)
{
	t_plane		*tmp_plane;

	tmp_plane = object->start_plane;
	while (tmp_plane)
	{
		if (tmp_plane->id != d->id_plane)
		{
			if (plane_intersection(d, tmp_plane))
			{
				if (d->solution < d->distance_light_object && d->solution >= 0)
				{
					*light_blocked = 1;
					break ;
				}
			}
		}
		tmp_plane = tmp_plane->next;
	}
}

int		check_if_light_is_blocked(t_datas *d, int *light_lock, t_object *object)
{
	*light_lock = 0;
	blocked_by_a_sphere(d, light_lock, object);
	if (*light_lock == 0)
		blocked_by_a_cylinder(d, light_lock, object);
	if (*light_lock == 0)
		blocked_by_a_cone(d, light_lock, object);
	if (*light_lock == 0)
		blocked_by_a_plane(d, light_lock, object);
	return (*light_lock);
}
