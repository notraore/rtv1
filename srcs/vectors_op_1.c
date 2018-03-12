/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	v_double_add(t_vector *a, double b)
{
	t_vector	r;

	r.x = a->x + b;
	r.y = a->y + b;
	r.z = a->z + b;
	return (r);
}

t_vector	v_double_subs(t_vector *a, double b)
{
	t_vector	r;

	r.x = a->x - b;
	r.y = a->y - b;
	r.z = a->z - b;
	return (r);
}

t_vector	v_double_mult(t_vector *a, double b)
{
	t_vector	r;

	r.x = a->x * b;
	r.y = a->y * b;
	r.z = a->z * b;
	return (r);
}

t_vector	v_double_div(t_vector *a, double b)
{
	t_vector	r;

	r.x = a->x / b;
	r.y = a->y / b;
	r.z = a->z / b;
	return (r);
}
