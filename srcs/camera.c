/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/01/08 17:05:10 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_camera(t_datas *d)
{
	d->camera.lookat = set_vector(0, 0, 0);
	d->camera.up = set_vector(0, 1, 0);
	d->camera.viewplane_width = (double)d->window_width;
	d->camera.viewplane_height = (double)d->window_height;
	d->camera.viewplane_distance = (double)d->window_width;
	d->camera.z_vector = v_v_subs(&d->camera.lookat, &d->camera.origin);
	d->camera.z_vector = normalize(&d->camera.z_vector);
	d->camera.y_vector = d->camera.up;
	d->camera.x_vector = v_v_mult(&d->camera.y_vector, &d->camera.z_vector);
	d->camera.y_vector = v_v_mult(&d->camera.z_vector, &d->camera.x_vector);
	d->matrix_camera_system = matrix_camera_system(&d->camera.x_vector,
	&d->camera.y_vector, &d->camera.z_vector);
	d->matrix_camera_origin = matrix_camera_origin(&d->camera.origin);
	viewplane_transformation(d);
}

void	camera_transformation(t_datas *d)
{
	d->rotation_matrix = rotation(d->rotate_x, d->rotate_y, d->rotate_z);
	d->matrix_camera_system = m4x4_m4x4_mult(&d->matrix_camera_system,
			&d->rotation_matrix);
	matrix_4x4_to_vectors(&d->camera.x_vector, &d->camera.y_vector,
			&d->camera.z_vector, &d->matrix_camera_system);
	d->translation_matrix = translation(d, &d->matrix_camera_system);
	d->matrix_camera_origin = m4x4_m4x1_mult_reduced(&d->translation_matrix,
			&d->matrix_camera_origin);
	matrix_4x1_to_vectors(&d->camera.origin, &d->matrix_camera_origin);
	viewplane_transformation(d);
}

void	viewplane_transformation(t_datas *d)
{
	t_vector	tmp_vpz;
	t_vector	tmp_vpy;
	t_vector	tmp_vpx;

	tmp_vpx = v_double_mult(&d->camera.x_vector,
			(d->camera.viewplane_width * 0.5));
	tmp_vpy = v_double_mult(&d->camera.y_vector,
			(d->camera.viewplane_height * 0.5));
	tmp_vpz = v_double_mult(&d->camera.z_vector,
			(d->camera.viewplane_distance));
	d->viewplane_point_up_left = v_v_add(&tmp_vpz, &tmp_vpy);
	d->viewplane_point_up_left = v_v_add(&d->camera.origin,
			&d->viewplane_point_up_left);
	d->viewplane_point_up_left = v_v_subs(&d->viewplane_point_up_left,
			&tmp_vpx);
}
