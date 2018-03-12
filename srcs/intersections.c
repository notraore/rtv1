/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		polygone_solutions(t_datas *d, t_poly *p)
{
	p->discriminant = (p->b * p->b) - (4 * p->a * p->c);
	if (p->discriminant < 0)
		return (0);
	else
	{
		if (p->discriminant == 0)
			d->solution = -(p->b / (2 * p->a));
		else
		{
			p->discriminant = sqrt(p->discriminant);
			p->s1 = (-p->b + p->discriminant) / (2 * p->a);
			p->s2 = (-p->b - p->discriminant) / (2 * p->a);
			d->solution = (p->s1 < p->s2 && p->s1 > 0) ? p->s1 : p->s2;
		}
		if (d->solution < 0)
			return (0);
		return (1);
	}
}

int		cone_intersection(t_datas *d, t_cone *cone)
{
	t_poly		p;

	p.cone_rayon = v_v_subs(&d->current_origin, &cone->vertex);
	p.a = 1 - ((1 + cone->tangent * cone->tangent) *
		(dot_product(&d->current_rayon, &cone->axis) *
		dot_product(&d->current_rayon, &cone->axis)));
	p.b = 2 * ((dot_product(&p.cone_rayon, &d->current_rayon) - ((1 +
		cone->tangent * cone->tangent) * (dot_product(&d->current_rayon,
		&cone->axis) * dot_product(&p.cone_rayon, &cone->axis)))));
	p.c = dot_product(&p.cone_rayon, &p.cone_rayon) - ((1 + cone->tangent *
		cone->tangent) * (dot_product(&p.cone_rayon, &cone->axis) *
		dot_product(&p.cone_rayon, &cone->axis)));
	if (!polygone_solutions(d, &p))
		return (0);
	cone->node = v_double_mult(&d->current_rayon, d->solution);
	cone->node = v_v_add(&d->current_origin, &cone->node);
	p.length = (dot_product(&d->current_rayon, &cone->axis) * d->solution) +
	dot_product(&p.cone_rayon, &cone->axis);
	p.tmp_node_normal = v_v_subs(&cone->node, &cone->vertex);
	cone->node_normal = v_double_mult(&cone->axis, p.length);
	cone->node_normal = v_double_mult(&cone->node_normal,
		(1 + cone->tangent * cone->tangent));
	cone->node_normal = v_v_subs(&p.tmp_node_normal, &cone->node_normal);
	cone->node_normal = normalize(&cone->node_normal);
	return (1);
}

int		cylinder_intersection(t_datas *d, t_cylinder *cylinder)
{
	t_poly		p;

	p.cylinder_rayon = v_v_subs(&d->current_origin, &cylinder->center);
	p.a = 1 - (dot_product(&d->current_rayon, &cylinder->axis) *
		dot_product(&d->current_rayon, &cylinder->axis));
	p.b = 2 * (dot_product(&p.cylinder_rayon, &d->current_rayon) -
		(dot_product(&d->current_rayon, &cylinder->axis) *
		dot_product(&p.cylinder_rayon, &cylinder->axis)));
	p.c = dot_product(&p.cylinder_rayon, &p.cylinder_rayon) -
		(dot_product(&p.cylinder_rayon, &cylinder->axis) *
		dot_product(&p.cylinder_rayon, &cylinder->axis)) -
		(cylinder->radius * cylinder->radius);
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
	if (!polygone_solutions(d, &p))
		return (0);
	cylinder->node = v_double_mult(&d->current_rayon, d->solution);
	cylinder->node = v_v_add(&d->current_origin, &cylinder->node);
	p.length = (dot_product(&d->current_rayon, &cylinder->axis) * d->solution)
		+ dot_product(&p.cylinder_rayon, &cylinder->axis);
	p.tmp_node_normal = v_v_subs(&cylinder->node, &cylinder->center);
	cylinder->node_normal = v_double_mult(&cylinder->axis, p.length);
	cylinder->node_normal = v_v_subs(&p.tmp_node_normal,
		&cylinder->node_normal);
	cylinder->node_normal = normalize(&cylinder->node_normal);
	return (1);
}

int		sphere_intersection(t_datas *d, t_sphere *sphere)
{
	t_poly		p;

	p.sphere_rayon = v_v_subs(&d->current_origin, &sphere->center);
	p.a = dot_product(&d->current_rayon, &d->current_rayon);
	p.b = 2 * (dot_product(&p.sphere_rayon, &d->current_rayon));
	p.c = dot_product(&p.sphere_rayon, &p.sphere_rayon) -
		(sphere->radius * sphere->radius);
	if (!polygone_solutions(d, &p))
		return (0);
	sphere->node = v_double_mult(&d->current_rayon, d->solution);
	sphere->node = v_v_add(&d->current_origin, &sphere->node);
	sphere->node_normal = v_v_subs(&sphere->node, &sphere->center);
	sphere->node_normal = normalize(&sphere->node_normal);
	return (1);
}

int		plane_intersection(t_datas *d, t_plane *plane)
{
	t_poly		p;

	p.plan_rayon = v_v_subs(&d->current_origin, &plane->point);
	p.a = dot_product(&plane->normal, &d->current_rayon);
	p.b = dot_product(&plane->normal, &p.plan_rayon);
	p.s = -(p.b / p.a);
	if (p.s < 0 || p.a == 0)
		return (0);
	d->solution = p.s;
	plane->node = v_double_mult(&d->current_rayon, d->solution);
	plane->node = v_v_add(&d->current_origin, &plane->node);
	if (p.a < 0)
		plane->node_normal = plane->normal;
	else
		plane->node_normal = v_double_mult(&plane->normal, (-1));
	return (1);
}
