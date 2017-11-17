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
	// ray.distance = 100000;

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
	// vector_normalize(&all->ray.dir);

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

	// oc.x = all->sph2.pos.x - all->ray.pos.x;
	// oc.y = all->sph2.pos.y - all->ray.pos.y;
	// oc.z = all->sph2.pos.z - all->ray.pos.z;

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

t_spot		create_spot(double x, double y, double z, double intens)
{
	t_spot	spot;

	spot.pos = create_vector(x, y, z);
	spot.ray.pos = create_vector(x, y, z);
	spot.intens = intens;
	return (spot);
}

t_color			create_color(double r, double g, double b)
{
	t_color	clr;

	clr.r = r;
	clr.g = g;
	clr.b = b;
	return (clr);
}

t_color			cast_light(t_all *all)
{
	t_color		clr;
	t_v			d;
	double 		angle;

	all->hit = vector_mult_scal(&all->hit, all->t);
	all->hit = vector_add(&all->ray.pos, &all->ray.dir);
	// printf("hit = %f || hit = %f || hit = %f\n", all->hit.x, all->hit.y, all->hit.z);
	all->normal = vector_sub(&all->sph.pos, &all->hit);
	all->normal = vector_div_scal(&all->normal, all->sph.r);
	all->spot.ray.dir = vector_sub(&all->spot.pos, &all->hit);
	all->spot.ray.dir = vector_normalize(&all->spot.ray.dir);
	// printf("all->spot.ray.dir.x = %f || all->spot.ray.dir.y = %f || all->spot.ray.dir.z = %f\n", all->spot.ray.dir.x, all->spot.ray.dir.y, all->spot.ray.dir.z);


	d = vector_mult_scal(&all->ray.dir, -1.0);
	// angle = dot_product(&d, &all->ray.dir);
	angle = dot_product(&d, &all->hit);

	if (angle <= 0)
	{
		angle = 0;
		return (create_color(0, 0, 0));
	}
	clr.r = all->sph.clr.r * all->spot.clr.r * angle;
	clr.g = all->sph.clr.g * all->spot.clr.g * angle;
	clr.b = all->sph.clr.b * all->spot.clr.b * angle;
	return (clr);
}

t_color			cast_light2(t_all *all)
{
	t_color		clr;
	double		d;

	all->hit = vector_add(&all->ray.pos, &all->ray.dir);
	vector_mult_scal(&all->hit, all->t);
	all->normal = vector_sub(&all->sph2.pos, &all->hit);
	all->normal = vector_normalize(&all->normal);
	all->spot.ray.dir = vector_sub(&all->hit, &all->spot.pos);
	all->spot.ray.dir = vector_normalize(&all->spot.ray.dir);

	d = dot_product(&all->normal, &all->spot.ray.dir);
	if (d < 0)
	{
		d = 0;
		return (create_color(0, 0, 0));
	}
	clr.r = all->spot.clr.r * all->sph2.clr.r * d;
	clr.g = all->spot.clr.g * all->sph2.clr.g * d;
	clr.b = all->spot.clr.b * all->sph2.clr.b * d;
	return (clr);
}

// t_color			cast_light3(t_all *all)
// {
// 	t_v			hit;
// 	t_v			normal;
// 	t_color		clr;
// 	double		d;

// 	hit = vector_add(&all->ray.pos, &all->ray.dir);
// 	// printf("hit = %f || hit = %f || hit = %f\n", hit.x, hit.y, hit.z);
// 	vector_mult_scal(&hit, all->t);
// 	normal = vector_sub(&all->plan.pos, &hit);
// 	normal = vector_normalize(&normal);
// 	all->spot.dir = vector_sub(&hit, &all->spot.pos);
// 	all->spot.dir = vector_normalize(&all->spot.dir);

// 	d = dot_product(&normal, &all->spot.dir);

// 	if (d < 0)
// 		d = 0;
// 	clr.r = all->sph.clr.r * all->spot.clr.r * d;
// 	clr.g = all->sph.clr.g * all->spot.clr.g * d;
// 	clr.b = all->sph.clr.b * all->spot.clr.b * d;
// // 	clr.r = all->plan.clr.r * d;
// // 	clr.g = all->plan.clr.g * d;
// // 	clr.b = all->plan.clr.b * d;
// 	return (clr);
// }

void		pixel_puts(t_color *clr, t_all *all)
{
	all->env->data[(all->x + all->y * WIDTH) * 4] = clr->b;
	all->env->data[(all->x + all->y * WIDTH) * 4 + 1] = clr->g;
	all->env->data[(all->x + all->y * WIDTH) * 4 + 2] = clr->r;
}


void		raytracing(t_all *all)
{
	int x1;
	int y1;

	all->y = 0;
	t_color clr;
	y1 = (HEIGHT / 2);
	while (all->y < HEIGHT)
	{
		all->x = 0;
		x1 = -(WIDTH / 2);
		while (all->x < WIDTH)
		{
			all->dist = 20000;
			all->ray = init_ray(all, x1, y1);
			if (cast_sphere(all) == true)
			{
				if (all->dist > all->t)
				{
					all->dist = all->t;
					clr = cast_light(all);
					// clr = create_color(255, 0, 0);
					// pixel_puts(&clr, all);
				}
			}
			// if (cast_sphere2(all) == true)
			// {
				// if (all->dist > all->t)
				// {
					// all->dist = all->t;
					// clr = create_color(0, 255, 0);
					// clr = cast_light2(all);
					// pixel_puts(&clr, all);
				// }
			// }
			// if (cast_plan(all) == true)
			// {
			// 	if (all->dist > all->t)
			// 	{
			// 		all->dist = all->t;
			// 		clr = cast_light3(all);
			// 		pixel_puts(&clr, all);
			// 	}
			// }
			// if (cast_cylindre(all) == true)
			// {
			// 	if (all->dist > all->t)
			// 	{
			// 		all->dist = all->t;
			// 		clr = create_color(255, 0, 255);
			// 	}
			// }
			pixel_puts(&clr, all);
			clr = create_color(0, 0, 0);
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
	all.env->data = mlx_get_data_addr(all.env->img, &all.env->bpp,
	&all.env->sl, &all.env->end);

	all.camera = init_cam(0, 0, -1000);
	all.spot = create_spot(500, 500, 150, 10);
	all.spot.clr = create_color(1, 1, 1);
	all.sph = create_sphere(0, -100, 255, 200);
	all.sph.clr = create_color(0.9, 0, 0);
	all.sph2 = create_sphere(150, -80, 5, 190);
	all.sph2.clr = create_color(0, 0, 0.9);
	// all.plan = create_plan(0, -80, 0);
	// all.plan.clr = create_color(125, 125, 125);
	raytracing(&all);
	mlx_put_image_to_window(all.env->mlx, all.env->win, all.env->img, 0, 0);
	mlx_hook(all.env->win, 17, (1L << 17), proper_exit, &all);
	mlx_hook(all.env->win, 2, (1L << 0), key_press, &all);
	mlx_loop(all.env->mlx);
	return (0);
}
