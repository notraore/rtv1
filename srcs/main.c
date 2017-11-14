/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:07:14 by notraore          #+#    #+#             */
/*   Updated: 2017/11/12 19:37:04 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_v			create_vector(double x, double y, double z)
{
	t_v		ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_cam		init_cam(double x, double y, double z)
{
	t_cam		cam;

	cam.cam_pos = create_vector(x, y, z);

	cam.vp.x = 0;
	cam.vp.y = 0;
	cam.vp.z = 0;
	return (cam);
}

t_ray		init_ray(t_all *all, int x1, int y1)
{
	t_ray ray;

	ray.pos = all->camera.cam_pos;
	ray.distance = 100000;

	all->camera.vp.x = x1;
	all->camera.vp.y = y1;

	// ray.dir.x = ray.pos.x - all->camera.vp.x;
	// ray.dir.y = ray.pos.y - all->camera.vp.y;
	// ray.dir.z = ray.pos.z - all->camera.vp.z;

	ray.dir.x = all->camera.vp.x - ray.pos.x;
	ray.dir.y = all->camera.vp.y - ray.pos.y;
	ray.dir.z = all->camera.vp.z - ray.pos.z;
	return (ray);
}

t_sph		create_sphere(double x, double y, double z, double radius)
{
	t_sph		sph;

	sph.pos = create_vector(x, y, z);
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
	if (all->delta < 0)
		return (false);
	if (all->delta == 0)
		all->delta = -b;
	if (all->delta > 0)
	{
		all->t1 = (-b + sqrt(all->delta)) / (2 * a);
		all->t2 = (-b - sqrt(all->delta)) / (2 * a);
		all->t = all->t1 >= all->t2 ? all->t2 : all->t1;
		return (true);
	}
	return (false);
}

bool		cast_sphere2(t_all *all)
{
	double	a;
	double	b;
	double	c;
	t_v		oc;

	oc.x = all->ray.pos.x - all->sph2.pos.x;
	oc.y = all->ray.pos.y - all->sph2.pos.y;
	oc.z = all->ray.pos.z - all->sph2.pos.z;
	vector_normalize(&all->ray.dir);

	a = all->ray.dir.x * all->ray.dir.x + all->ray.dir.y * all->ray.dir.y + all->ray.dir.z * all->ray.dir.z;
	b = 2 * (all->ray.dir.x * (oc.x) + all->ray.dir.y * (oc.y) + all->ray.dir.z * (oc.z));
	c = ((oc.x * oc.x) + (oc.y * oc.y) + (oc.z * oc.z)) - all->sph2.r * all->sph2.r;

	all->delta = b * b - 4 * a * c;
	if (all->delta < 0)
		return (false);
	if (all->delta == 0)
		all->delta = -b;
	if (all->delta > 0)
	{
		all->t1 = (-b + sqrt(all->delta)) / (2 * a);
		all->t2 = (-b - sqrt(all->delta)) / (2 * a);
		all->t = all->t1 > all->t2 ? all->t2 : all->t1;
		return (true);
	}
	return (false);
}

t_plan		create_plan(double x, double y, double z)
{

	t_plan		plan;

	plan.normal = create_vector(0, 1, 0);
	plan.pos = create_vector(x, y, z);
	return (plan);
}


bool		cast_plan(t_all *all)
{
	t_v		oc;
	double	a;
	double	b;
	double	s;
	oc = vector_sub(&all->plan.pos, &all->camera.cam_pos);
	a = dot_product(&all->plan.normal, &oc);
	b = dot_product(&all->plan.normal, &all->ray.dir);
	s = -(a / b);
	if (a == 0 || s < 0)
		return (false);
	all->t = s;
	return (true);
}

// t_spot		create_spot(double x, double y, double z, double intens)
// {
// 	t_spot	spot;

// 	spot.pos = create_vector(x, y, z);
// 	spot.intens = intens;
// 	return (spot);
// }

// int		plane_intersection(t_datas *d)
// {
// 	double		a;
// 	double		b;
// 	double		s;
// 	t_vector	plan_cam;

// 	plan_cam = v_v_subs(&d->camera.origin, &d->plane.point);
// 	a = dot_product(&d->plane.normal, &d->camera.rayon);
// 	b = dot_product(&d->plane.normal, &plan_cam);
// 	if (b == 0)
// 		return (0);
// 	s = -(b / a);
// 	if (s < 0)
// 		return (0);
// 	else 
// 	{
// 		d->solution = s;
// 		return (1);
// 	}
// }


void		raytracing(t_all *all)
{
	int x1;
	int y1;

	all->y = 0;
	y1 = (HEIGHT / 2);
	while (all->y <= HEIGHT)
	{
		all->x = 0;
		x1 = -(WIDTH / 2);
		while (all->x <= WIDTH)
		{
			all->dist = 20000;
			all->clr = BLACK;
			all->ray = init_ray(all, x1, y1);
			if (cast_sphere(all) == true)
			{
				if (all->dist > all->t)
				{
					all->clr = RED;
					all->dist = all->t;
				}
			}
			if (cast_sphere2(all) == true)
			{
				if (all->dist > all->t)
				{
					all->clr = BLUE / 2;
					all->dist = all->t;
				}
			}
			if (cast_plan(all) == true)
			{
				if (all->dist > all->t)
				{
					all->clr = GREY;
					all->dist = all->t;
				}
			}
			if (all->x > 0 && all->x < WIDTH && all->y >= 0 && all->y < HEIGHT)
				all->env->data[all->x + all->y * WIDTH] = all->clr;
			all->x++;
			x1++;
		}
		all->y++;
		y1--;
	}
}

int			main(void)
{
	t_mlx		mlx;
	t_all		all;

	all.env = &mlx;
	all.env->mlx = mlx_init();
	all.env->win = mlx_new_window(all.env->mlx, WIDTH, HEIGHT, "RTv1");
	all.env->img = mlx_new_image(all.env->mlx, WIDTH, HEIGHT);
	all.env->data = (int *)mlx_get_data_addr(all.env->img, &all.env->bpp,
	&all.env->sl, &all.env->end);

	all.camera = init_cam(0, 0, -1000);
	// all.spot.pos = create_spot(-400, 400, 10, 10);
	all.sph = create_sphere(-100, -80, 300, 90);
	all.sph2 = create_sphere(0, -80, 300, 90);
	all.plan = create_plan(0, -80, 0);
	raytracing(&all);
	mlx_put_image_to_window(all.env->mlx, all.env->win, all.env->img, 0, 0);
	mlx_hook(all.env->win, 17, (1L << 17), proper_exit, &all);
	mlx_hook(all.env->win, 2, (1L << 0), key_press, &all);
	mlx_loop(all.env->mlx);
	return (0);
}
