/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			degree_to_radian(double degree_angle)
{
	double		radian_angle;

	radian_angle = degree_angle * (2.0 * M_PI / 360.0);
	return (radian_angle);
}

t_matrix4x4		m4x4_m4x4_mult(t_matrix4x4 *camera_matrix,
t_matrix4x4 *rotation)
{
	t_matrix4x4	final_matrix;
	int			i;
	int			j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			final_matrix.m[j][i] =
			rotation->m[j][0] * camera_matrix->m[0][i] +
			rotation->m[j][1] * camera_matrix->m[1][i] +
			rotation->m[j][2] * camera_matrix->m[2][i] +
			rotation->m[j][3] * camera_matrix->m[3][i];
			i++;
		}
		j++;
	}
	return (final_matrix);
}

void			matrix_4x4_to_vectors(t_vector *a, t_vector *b,
t_vector *c, t_matrix4x4 *matrix)
{
	a->x = matrix->m[0][0];
	a->y = matrix->m[0][1];
	a->z = matrix->m[0][2];
	b->x = matrix->m[1][0];
	b->y = matrix->m[1][1];
	b->z = matrix->m[1][2];
	c->x = matrix->m[2][0];
	c->y = matrix->m[2][1];
	c->z = matrix->m[2][2];
}
