/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			proper_exit(t_datas *d)
{
	mlx_destroy_window(d->mlx.mlx_ptr, d->mlx.win_ptr);
	free(d->objects);
	exit(EXIT_SUCCESS);
	return (0);
}

void		inputs(int keycode, t_datas *d)
{
	if (keycode == 2)
		d->move_x = 25;
	else if (keycode == 0)
		d->move_x = -25;
	else if (keycode == 12)
		d->move_y = 25;
	else if (keycode == 14)
		d->move_y = -25;
	else if (keycode == 13)
		d->move_z = 25;
	else if (keycode == 1)
		d->move_z = -25;
	else if (keycode == 126)
		d->rotate_x = 1.5;
	else if (keycode == 125)
		d->rotate_x = -1.5;
	else if (keycode == 123)
		d->rotate_y = 1.5;
	else if (keycode == 124)
		d->rotate_y = -1.5;
	else if (keycode == 6)
		d->rotate_z = 1.5;
	else if (keycode == 7)
		d->rotate_z = -1.5;
}

void		reset_mov_rotate(t_datas *d)
{
	d->move_x = 0;
	d->move_y = 0;
	d->move_z = 0;
	d->rotate_x = 0;
	d->rotate_y = 0;
	d->rotate_z = 0;
}

int			key_functions(int keycode, t_datas *d)
{
	if (keycode == 53)
		proper_exit(d);
	else if (keycode == 2 || keycode == 0 || keycode == 12 || keycode == 14 ||
	keycode == 13 || keycode == 1 || keycode == 126 || keycode == 123 ||
	keycode == 125 || keycode == 124 || keycode == 6 || keycode == 7 ||
	keycode == 49 || keycode == 15)
	{
		inputs(keycode, d);
		if (keycode == 49)
			d->pixelize = d->pixelize == 1 ? 0 : 1;
		else if (keycode == 15)
			d->aa_flag = d->aa_flag == 1 ? 0 : 1;
		ft_bzero(d->mlx.data, (d->window_width * d->window_height) * 4);
		camera_transformation(d);
		if (d->aa_flag == 1 && d->pixelize == 0)
			aa_tracer(d, 1);
		else if (d->pixelize == 1)
			pixel_tracer(d, 13);
		else
			ray_tracer(d);
		mlx_put_image_to_window(d->mlx.mlx_ptr, d->mlx.win_ptr,
		d->mlx.img_ptr, 0, 0);
	}
	reset_mov_rotate(d);
	return (0);
}
