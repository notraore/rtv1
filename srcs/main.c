/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:07:14 by notraore          #+#    #+#             */
/*   Updated: 2017/11/07 14:47:19 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"



t_cam		init_cam(double x, double y, double z)
{
	t_cam		cam;

	cam.cam_pos.x = x;
	cam.cam_pos.y = y;
	cam.cam_pos.z = z;

	cam.vp.x = 0;
	cam.vp.y = 0;
	cam.vp.z = 0;
	return (cam);
}

t_ray		init_ray(t_all *all)
{
	t_ray ray;

	ray.pos = all->camera.cam_pos;
	ray.distance = 100000;

	all->camera.vp.x = all->x;
	all->camera.vp.y = all->y;

	ray.dir.x = ray.pos.x - all->camera.vp.x;
	ray.dir.y = ray.pos.y - all->camera.vp.y;
	ray.dir.z = ray.pos.z - all->camera.vp.z;
	return (ray);
}

t_sph		create_sphere(double x, double y, double z, double radius)
{
	t_sph		sph;

	sph.pos.x = x;
	sph.pos.y = y;
	sph.pos.z = z;
	sph.r = radius;

	return (sph);
}

bool		cast_sphere(t_all *all)
{
	double	a;
	double	b;
	double	c;

	t_v		oc;

	oc.x = all->ray.pos.x - all->sph.pos.x;
	oc.y = all->ray.pos.y - all->sph.pos.y;
	oc.z = all->ray.pos.z - all->sph.pos.z;
	vector_normalize(&all->ray.dir);

	a = all->ray.dir.x * all->ray.dir.x + all->ray.dir.y * all->ray.dir.y + all->ray.dir.z * all->ray.dir.z;
	b = 2 * (all->ray.dir.x * (oc.x) + all->ray.dir.y * (oc.y) + all->ray.dir.z * (oc.z));
	c = ((oc.x * oc.x) + (oc.y * oc.y) + (oc.z * oc.z)) - all->sph.r * all->sph.r;

	all->delta = b * b - 4 * a * c;
	if (all->delta == 0)
		return (true);
	return (false);
}

// bool		cast_plan(t_all *all)
// {

// }

void		raytracing(t_all *all)
{
	all->y = 0;

	while (all->y <= HEIGHT)
	{
		all->x = 0;
		while (all->x <= WIDTH)
		{
			all->ray = init_ray(all);
			if (cast_sphere(all) == true)
				all->env->data[all->x + all->y * WIDTH] = RED;
			all->x++;
		}
		all->y++;
	}
}

int			main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_mlx		mlx;
	t_all		all;

	all.env = &mlx;
	all.env->mlx = mlx_init();
	all.env->win = mlx_new_window(all.env->mlx, WIDTH, HEIGHT, "RTv1");
	all.env->img = mlx_new_image(all.env->mlx, WIDTH, HEIGHT);
	all.env->data = (int *)mlx_get_data_addr(all.env->img, &all.env->bpp,
	&all.env->sl, &all.env->end);

	all.camera = init_cam((double)WIDTH / 2, (double)HEIGHT / 2, -400);
	printf("all.cam.x = %f\n", all.camera.cam_pos.x);
	printf("all.cam.y = %f\n", all.camera.cam_pos.y);

	all.sph = create_sphere(400, 300, 50, 200);
	raytracing(&all);

	mlx_put_image_to_window(all.env->mlx, all.env->win, all.env->img, 0, 0);
	mlx_hook(all.env->win, 17, (1L << 17), proper_exit, &all);
	mlx_hook(all.env->win, 2, (1L << 0), key_press, &all);
	mlx_loop(all.env->mlx);
	return (0);
}
