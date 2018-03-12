/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_transformations(t_datas *d)
{
	d->move_x = 0;
	d->move_y = 0;
	d->move_z = 0;
	d->rotate_x = 0;
	d->rotate_y = 0;
	d->rotate_z = 0;
	d->pixelize = 0;
}

void		display_window(t_datas *d, t_object *object)
{
	if (!(d->objects = object))
		ft_kill("Assignation error : d->object in main.c");
	if (!(d->mlx.mlx_ptr = mlx_init()))
		ft_kill("mlx_init error");
	if (!(d->mlx.win_ptr = mlx_new_window(d->mlx.mlx_ptr, d->window_width,
		d->window_height, "RTv1")))
		ft_kill("mlx_new_window error");
	if (!(d->mlx.img_ptr = mlx_new_image(d->mlx.mlx_ptr, d->window_width,
		d->window_height)))
		ft_kill("mlx_new_image error");
	if (!(d->mlx.data = (unsigned char*)mlx_get_data_addr(d->mlx.img_ptr,
		&d->mlx.bpp, &d->mlx.l_size, &d->mlx.endian)))
		ft_kill("mlx_get_data_addr error");
	init_transformations(d);
	init_camera(d);
	camera_transformation(d);
	ray_tracer(d);
	mlx_hook(d->mlx.win_ptr, 2, (1L << 0), key_functions, d);
	mlx_hook(d->mlx.win_ptr, 17, (1L << 17), proper_exit, d);
	mlx_put_image_to_window(d->mlx.mlx_ptr, d->mlx.win_ptr,
		d->mlx.img_ptr, 0, 0);
	mlx_loop(d->mlx.mlx_ptr);
	mlx_destroy_window(d->mlx.mlx_ptr, d->mlx.win_ptr);
}

int			check_args(char *argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '.' && argv[i + 1] == 'r' && argv[i + 2] == 't'
		&& argv[i + 3] == 'v' && argv[i + 4] == '1')
			return (1);
		i++;
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_object	*object;
	t_datas		d;
	int			ret;

	if (argc != 2)
		ft_print_err(argc);
	if (!(object = (t_object*)ft_memalloc(sizeof(t_object))))
		ft_kill("Malloc error : object refereced in main.c");
	if (!(check_args(argv[1])))
		ft_kill("Bad file, check your scnene name");
	if (!(ret = parsing(&d, object, argv[1])))
		ft_kill("parsing error");
	display_window(&d, object);
	return (0);
}
