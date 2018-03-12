/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_intersection(t_datas *d, t_object *object)
{
	int			printable;
	t_cylinder	*tmp_cylinder;
	t_sphere	*tmp_sphere;
	t_cone		*tmp_cone;
	t_plane		*tmp_plane;

	d->current_origin = d->camera.origin;
	d->current_rayon = d->camera.rayon;
	printable = 0;
	tmp_sphere = object->start_sphere;
	tmp_cylinder = object->start_cylinder;
	tmp_cone = object->start_cone;
	tmp_plane = object->start_plane;
	register_sphere(d, tmp_sphere, &printable);
	register_cylinder(d, tmp_cylinder, &printable);
	register_cone(d, tmp_cone, &printable);
	register_plane(d, tmp_plane, &printable);
	if (printable == 1)
		get_color(d, object);
}

void		ray_tracer(t_datas *d)
{
	int			x;
	int			y;
	t_vector	vwp_point;
	t_vector	tmp_vp_pointx;
	t_vector	tmp_vp_pointy;

	y = 0;
	while (y < d->window_height)
	{
		x = 0;
		while (x < d->window_width)
		{
			d->color_finale = set_color(0, 0, 0);
			d->distance = 100000000;
			tmp_vp_pointx = v_double_mult(&d->camera.x_vector, x);
			tmp_vp_pointy = v_double_mult(&d->camera.y_vector, y);
			vwp_point = v_v_add(&d->viewplane_point_up_left, &tmp_vp_pointx);
			vwp_point = v_v_subs(&vwp_point, &tmp_vp_pointy);
			d->camera.rayon = v_v_subs(&vwp_point, &d->camera.origin);
			d->camera.rayon = normalize(&d->camera.rayon);
			get_intersection(d, d->objects);
			print_color(&d->color_finale, d, x++, y);
		}
		y++;
	}
}
