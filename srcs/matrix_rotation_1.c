/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix4x4		matrix_camera_system(t_vector *a, t_vector *b, t_vector *c)
{
	t_matrix4x4		camera_matrix;

	camera_matrix.m[0][0] = a->x;
	camera_matrix.m[0][1] = a->y;
	camera_matrix.m[0][2] = a->z;
	camera_matrix.m[0][3] = 0.0;
	camera_matrix.m[1][0] = b->x;
	camera_matrix.m[1][1] = b->y;
	camera_matrix.m[1][2] = b->z;
	camera_matrix.m[1][3] = 0.0;
	camera_matrix.m[2][0] = c->x;
	camera_matrix.m[2][1] = c->y;
	camera_matrix.m[2][2] = c->z;
	camera_matrix.m[2][3] = 0.0;
	camera_matrix.m[3][0] = 0.0;
	camera_matrix.m[3][1] = 0.0;
	camera_matrix.m[3][2] = 0.0;
	camera_matrix.m[3][3] = 1.0;
	return (camera_matrix);
}

void			rotation_matrix(t_matrix4x4 *rotation, t_poly *p)
{
	rotation->m[0][0] = p->c * p->e;
	rotation->m[0][1] = -p->c * p->f;
	rotation->m[0][2] = p->d;
	rotation->m[0][3] = 0.0;
	rotation->m[1][0] = p->bd * p->e + p->a * p->f;
	rotation->m[1][1] = -p->bd * p->f + p->a * p->e;
	rotation->m[1][2] = -p->b * p->c;
	rotation->m[1][3] = 0.0;
	rotation->m[2][0] = -p->ad * p->e + p->b * p->f;
	rotation->m[2][1] = p->ad * p->f + p->b * p->e;
	rotation->m[2][2] = p->a * p->c;
	rotation->m[2][3] = 0.0;
	rotation->m[3][0] = 0.0;
	rotation->m[3][1] = 0.0;
	rotation->m[3][2] = 0.0;
	rotation->m[3][3] = 1.0;
}

t_matrix4x4		rotation(double degree_x, double degree_y, double degree_z)
{
	t_poly		p;
	t_matrix4x4	rotation;

	p.radian_x = degree_to_radian(degree_x);
	p.radian_y = degree_to_radian(degree_y);
	p.radian_z = degree_to_radian(degree_z);
	p.a = cos(p.radian_x);
	p.b = sin(p.radian_x);
	p.c = cos(p.radian_y);
	p.d = sin(p.radian_y);
	p.e = cos(p.radian_z);
	p.f = sin(p.radian_z);
	p.ad = p.a * p.d;
	p.bd = p.b * p.d;
	rotation_matrix(&rotation, &p);
	return (rotation);
}
