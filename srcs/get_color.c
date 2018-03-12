/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		get_specular(t_light *light, t_vector *view, t_vector *node)
{
	t_vector	tmp;
	t_vector	r;
	double		reflect;
	double		specular;

	reflect = dot_product(&light->rayon, node);
	tmp = v_double_mult(node, 2);
	r = v_double_mult(&tmp, reflect);
	r = v_v_subs(&r, &light->rayon);
	specular = 0.2 * powf(dot_product(view, &r), 50) * 4;
	return (specular);
}

void		light_intensity(t_get_light *v, t_datas *d)
{
	double	specular;

	v->tmp_angle = v_double_mult(&v->tmp_light->rayon, (-1));
	v->tmp_light->angle = dot_product(&d->current_node_normal,
	&v->tmp_angle);
	specular = d->brightness * get_specular(v->tmp_light, &v->view_rayon,
		&v->ray_normal);
	if (v->tmp_light->angle > 0)
	{
		v->tmp_color_to_add = c_c_mult(&d->current_color,
			&v->tmp_light->color);
		v->tmp_color_to_add = c_double_add(&v->tmp_color_to_add, specular);
		v->color_to_add = c_double_mult(&v->tmp_color_to_add,
			v->tmp_light->angle);
	}
}

void		get_color(t_datas *d, t_object *object)
{
	t_get_light		v;

	v.ray_normal = d->current_node_normal;
	v.view_rayon = d->current_rayon;
	v.tmp_light = object->start_light;
	d->color_finale = set_color(0, 0, 0);
	while (v.tmp_light)
	{
		v.color_to_add = set_color(0, 0, 0);
		v.tmp_light->rayon = v_v_subs(&d->current_node,
			&v.tmp_light->origin);
		d->distance_light_object = magnitude(&v.tmp_light->rayon);
		v.tmp_light->rayon = normalize(&v.tmp_light->rayon);
		d->current_origin = v.tmp_light->origin;
		d->current_rayon = v.tmp_light->rayon;
		if (!check_if_light_is_blocked(d, &v.light_blocked, object))
			light_intensity(&v, d);
		d->color_finale = c_c_add(&d->color_finale, &v.color_to_add);
		v.tmp_light = v.tmp_light->next;
	}
}
