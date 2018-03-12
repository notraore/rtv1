/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_pixel		pixel_vp_init(t_pixel *pxl, t_datas *d)
{
	t_pixel new;

	new = *pxl;
	new.tmpx = new.x;
	new.tmpy = new.y;
	new.tmp_vp_pointx = v_double_mult(&d->camera.x_vector, new.x);
	new.tmp_vp_pointy = v_double_mult(&d->camera.y_vector, new.y);
	new.viewplane_point = v_v_add(&d->viewplane_point_up_left,
	&new.tmp_vp_pointx);
	new.viewplane_point = v_v_subs(&new.viewplane_point, &new.tmp_vp_pointy);
	return (new);
}

/*
**Sample = pixel square lenght, set by default to 13.
*/

void		pixel_tracer(t_datas *d, int sample)
{
	t_pixel		pxl;

	pxl.y = 0;
	while (pxl.y < d->window_height)
	{
		pxl.x = 0;
		while (pxl.x < d->window_width)
		{
			d->color_finale = set_color(0, 0, 0);
			d->distance = 100000;
			pxl = pixel_vp_init(&pxl, d);
			d->camera.rayon = v_v_subs(&pxl.viewplane_point, &d->camera.origin);
			d->camera.rayon = normalize(&d->camera.rayon);
			get_intersection(d, d->objects);
			while (pxl.y++ < pxl.tmpy + sample)
			{
				pxl.x = pxl.x != pxl.tmpx ? pxl.x - sample : pxl.x;
				while (pxl.x < pxl.tmpx + sample)
					print_color(&d->color_finale, d, pxl.x++, pxl.y);
			}
			pxl.y = pxl.tmpy;
		}
		pxl.y += sample;
	}
}
