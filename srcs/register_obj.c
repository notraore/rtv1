/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	register_cylinder(t_datas *d, t_cylinder *tmp_cylinder, int *printable)
{
	while (tmp_cylinder)
	{
		if (cylinder_intersection(d, tmp_cylinder))
		{
			if (d->solution < d->distance && d->solution >= 0)
			{
				*printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_cylinder->node;
				d->current_node_normal = tmp_cylinder->node_normal;
				d->current_color = tmp_cylinder->color;
				d->brightness = tmp_cylinder->brightness;
				d->id_cylinder = tmp_cylinder->id;
				d->id_sphere = -1;
				d->id_plane = -1;
				d->id_cone = -1;
			}
		}
		tmp_cylinder = tmp_cylinder->next;
	}
}

void	register_cone(t_datas *d, t_cone *tmp_cone, int *printable)
{
	while (tmp_cone)
	{
		if (cone_intersection(d, tmp_cone))
		{
			if (d->solution < d->distance && d->solution >= 0)
			{
				*printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_cone->node;
				d->current_node_normal = tmp_cone->node_normal;
				d->current_color = tmp_cone->color;
				d->brightness = tmp_cone->brightness;
				d->id_cone = tmp_cone->id;
				d->id_sphere = -1;
				d->id_cylinder = -1;
				d->id_plane = -1;
			}
		}
		tmp_cone = tmp_cone->next;
	}
}

void	register_sphere(t_datas *d, t_sphere *tmp_sphere, int *printable)
{
	while (tmp_sphere)
	{
		if (sphere_intersection(d, tmp_sphere))
		{
			if (d->solution < d->distance && d->solution >= 0)
			{
				*printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_sphere->node;
				d->current_node_normal = tmp_sphere->node_normal;
				d->current_color = tmp_sphere->color;
				d->brightness = tmp_sphere->brightness;
				d->id_sphere = tmp_sphere->id;
				d->id_cylinder = -1;
				d->id_cone = -1;
				d->id_plane = -1;
			}
		}
		tmp_sphere = tmp_sphere->next;
	}
}

void	register_plane(t_datas *d, t_plane *tmp_plane, int *printable)
{
	while (tmp_plane)
	{
		if (plane_intersection(d, tmp_plane))
		{
			if (d->solution < d->distance && d->solution >= 0)
			{
				*printable = 1;
				d->distance = d->solution;
				d->current_node = tmp_plane->node;
				d->current_node_normal = tmp_plane->node_normal;
				d->current_color = tmp_plane->color;
				d->brightness = tmp_plane->brightness;
				d->id_plane = tmp_plane->id;
				d->id_sphere = -1;
				d->id_cone = -1;
				d->id_cylinder = -1;
			}
		}
		tmp_plane = tmp_plane->next;
	}
}
