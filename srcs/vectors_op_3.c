/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	v_v_subs(t_vector *a, t_vector *b)
{
	t_vector	r;

	r.x = a->x - b->x;
	r.y = a->y - b->y;
	r.z = a->z - b->z;
	return (r);
}

t_vector	v_v_mult(t_vector *a, t_vector *b)
{
	t_vector	r;

	r.x = (a->y * b->z) - (a->z * b->y);
	r.y = (a->z * b->x) - (a->x * b->z);
	r.z = (a->x * b->y) - (a->y * b->x);
	return (r);
}
