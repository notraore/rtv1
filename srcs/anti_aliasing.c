/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/03/12 16:35:58 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		anti_aliasing_clr_merge(t_color *anti, t_color *clr)
{
	anti->r += clr->r;
	anti->g += clr->g;
	anti->b += clr->b;
}

t_anti_a	antialias_loop_init(t_anti_a *anti, t_datas *d, int sample)
{
	t_anti_a new;

	new = *anti;
	new.x1 = 0;
	while (new.x1 < sample)
	{
		d->distance = 100000;
		new.tmp_vp_pointx = v_double_mult(&d->camera.x_vector, new.x + new.x1);
		new.tmp_vp_pointy = v_double_mult(&d->camera.y_vector, new.y + new.y1);
		new.viewplane_point = v_v_add(&d->viewplane_point_up_left,
		&new.tmp_vp_pointx);
		new.viewplane_point = v_v_subs(&new.viewplane_point,
		&new.tmp_vp_pointy);
		d->camera.rayon = v_v_subs(&new.viewplane_point, &d->camera.origin);
		d->camera.rayon = normalize(&d->camera.rayon);
		get_intersection(d, d->objects);
		anti_aliasing_clr_merge(&new.aaclr, &d->color_finale);
		new.x1 += 0.25;
	}
	return (new);
}

void		aa_tracer(t_datas *d, int sample)
{
	t_anti_a	aa;

	aa.y = 0;
	while (aa.y < d->window_height)
	{
		aa.x = 0;
		while (aa.x < d->window_width)
		{
			aa.y1 = 0;
			aa.aaclr = set_color(0, 0, 0);
			d->color_finale = set_color(0, 0, 0);
			while (aa.y1 < sample)
			{
				aa = antialias_loop_init(&aa, d, sample);
				aa.y1 += 0.25;
			}
			aa.aaclr = c_double_div(&aa.aaclr, 16);
			print_color(&aa.aaclr, d, aa.x, aa.y);
			aa.x++;
		}
		aa.y++;
	}
}
