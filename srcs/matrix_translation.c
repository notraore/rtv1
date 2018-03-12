/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix4x1		m4x4_m4x1_mult_reduced(t_matrix4x4 *translation,
t_matrix4x1 *matrix)
{
	t_matrix4x1	matrix_ret;

	matrix_ret.m[0][0] = translation->m[0][3] + matrix->m[0][0];
	matrix_ret.m[1][0] = translation->m[1][3] + matrix->m[1][0];
	matrix_ret.m[2][0] = translation->m[2][3] + matrix->m[2][0];
	return (matrix_ret);
}

void			matrix_4x1_to_vectors(t_vector *a, t_matrix4x1 *matrix)
{
	a->x = matrix->m[0][0];
	a->y = matrix->m[1][0];
	a->z = matrix->m[2][0];
}

t_matrix4x1		matrix_camera_origin(t_vector *a)
{
	t_matrix4x1		matrix_ret;

	matrix_ret.m[0][0] = a->x;
	matrix_ret.m[1][0] = a->y;
	matrix_ret.m[2][0] = a->z;
	matrix_ret.m[3][0] = 1.0;
	return (matrix_ret);
}

void			update_system_translation(t_datas *d, t_matrix4x4 *rot)
{
	d->x1 = 0;
	d->y1 = 0;
	d->z1 = 0;
	if (d->move_x != 0)
	{
		d->x1 = d->move_x * rot->m[0][0];
		d->y1 = d->move_x * rot->m[0][1];
		d->z1 = d->move_x * rot->m[0][2];
	}
	else if (d->move_y != 0)
	{
		d->x1 = d->move_y * rot->m[1][0];
		d->y1 = d->move_y * rot->m[1][1];
		d->z1 = d->move_y * rot->m[1][2];
	}
	else if (d->move_z != 0)
	{
		d->x1 = d->move_z * rot->m[2][0];
		d->y1 = d->move_z * rot->m[2][1];
		d->z1 = d->move_z * rot->m[2][2];
	}
}

t_matrix4x4		translation(t_datas *d, t_matrix4x4 *rot)
{
	t_matrix4x4		translation;

	update_system_translation(d, rot);
	translation.m[0][0] = 1.0;
	translation.m[0][1] = 0.0;
	translation.m[0][2] = 0.0;
	translation.m[0][3] = d->x1;
	translation.m[1][0] = 0.0;
	translation.m[1][1] = 1.0;
	translation.m[1][2] = 0.0;
	translation.m[1][3] = d->y1;
	translation.m[2][0] = 0.0;
	translation.m[2][1] = 0.0;
	translation.m[2][2] = 1.0;
	translation.m[2][3] = d->z1;
	translation.m[3][0] = 0.0;
	translation.m[3][1] = 0.0;
	translation.m[3][2] = 0.0;
	translation.m[3][3] = 1.0;
	return (translation);
}
