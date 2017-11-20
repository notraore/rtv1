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
	t_v			ret;

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
	t_ray		ray;

	ray.pos = all->camera.cam_pos;
	all->camera.vp.x = x1;
	all->camera.vp.y = y1;
	all->camera.vp.z = 0;
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

bool		cast_sphere(t_all *all, t_ray *t, t_sph *sph)
{
	double		a;
	double		b;
	double		c;
	t_v			o;

	o.x = t->pos.x - sph[all->nbr].pos.x;
	o.y = t->pos.y - sph[all->nbr].pos.y;
	o.z = t->pos.z - sph[all->nbr].pos.z;
	a = t->dir.x * t->dir.x + t->dir.y * t->dir.y + t->dir.z * t->dir.z;
	b = 2 * (t->dir.x * (o.x) + t->dir.y * (o.y) + t->dir.z * (o.z));
	c = ((o.x * o.x) + (o.y * o.y) + (o.z * o.z)) - sph[all->nbr].r * sph[all->nbr].r;
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

t_plan		create_plan(double x, double y, double z)
{
	t_plan		plan;

	plan.normal = create_vector(0, 1, 0);
	plan.pos = create_vector(x, y, z);
	return (plan);
}

bool		cast_plan(t_all *all)
{
	t_v			o;
	double		a;
	double		b;
	double		s;

	o = vector_sub(&all->plan.pos, &all->camera.cam_pos);
	a = dot_product(&all->plan.normal, &o);
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

t_color		create_color(double r, double g, double b, double a)
{
	t_color		clr;

	clr.r = r;
	clr.g = g;
	clr.b = b;
	clr.a = a;
	return (clr);
}

t_color		cast_light(t_all *all)
{
	t_color		clr;
	t_v			d;
	double		angle;

	all->hit = vector_mult_scal(&all->ray.dir, all->t);
	all->hit = vector_add(&all->ray.pos, &all->hit);
	all->normal = vector_sub(&all->sph[all->nbr].pos, &all->hit);
	all->normal = vector_div_scal(&all->normal, all->sph[all->nbr].r);
	all->spot.ray.dir = vector_sub(&all->spot.pos, &all->hit);
	all->spot.ray.dir = vector_normalize(&all->spot.ray.dir);
	d = vector_mult_scal(&all->spot.ray.dir, (-1.0));
	angle = dot_product(&d, &all->normal);
	if (angle <= 0)
		return (create_color(0, 0, 0, 0));
	clr.r = all->sph[all->nbr].clr.r * all->spot.clr.r * angle;
	clr.g = all->sph[all->nbr].clr.g * all->spot.clr.g * angle;
	clr.b = all->sph[all->nbr].clr.b * all->spot.clr.b * angle;
	return (clr);
}

t_color		cast_light3(t_all *all)
{
	t_color		clr;
	t_v			d;
	double		angle;

	all->hit = vector_mult_scal(&all->ray.dir, all->t);
	all->hit = vector_add(&all->ray.pos, &all->hit);
	all->spot.ray.dir = vector_sub(&all->spot.pos, &all->hit);
	all->spot.ray.dir = vector_normalize(&all->spot.ray.dir);
	d = vector_mult_scal(&all->spot.ray.dir, (-1.0));
	angle = dot_product(&d, &all->plan.normal);
	if (angle <= 0)
		return (create_color(0, 0, 0, 0));
	all->shadow.dir = vector_sub(&all->hit, &all->spot.pos);
	all->shadow.pos = all->hit;
	if (cast_sphere(all, &all->shadow, &all->sph[all->nbr]) == true)
		return (create_color(0, 0, 0, 0));
	clr.r = all->plan.clr.r * all->spot.clr.r * angle;
	clr.g = all->plan.clr.g * all->spot.clr.g * angle;
	clr.b = all->plan.clr.b * all->spot.clr.b * angle;
	return (clr);
}

void		pixel_puts(t_color *clr, t_all *all)
{
	all->env->data[(all->x + all->y * WIDTH) * 4] = clr->b * 255.0;
	all->env->data[(all->x + all->y * WIDTH) * 4 + 1] = clr->g * 255.0;
	all->env->data[(all->x + all->y * WIDTH) * 4 + 2] = clr->r * 255.0;
	all->env->data[(all->x + all->y * WIDTH) * 4 + 3] = clr->a * 255.0;
}

void		raytracing(t_all *all)
{
	int			x1;
	int			y1;
	t_color		clr;

	all->y = 0;
	y1 = (HEIGHT / 2);
	all->nbr = 1;
	while (all->y < HEIGHT)
	{
		all->x = 0;
		x1 = -(WIDTH / 2);
		while (all->x < WIDTH)
		{
			all->dist = 20000;
			all->ray = init_ray(all, x1, y1);
			while (all->nbr < all->sphnbr)
			{
				if (cast_sphere(all, &all->ray, &all->sph[all->nbr]) == true && all->dist > all->t)
				{
					printf("all->nbr = %zu\n", all->nbr);
					all->dist = all->t;
					clr = cast_light(all);
				}
				all->nbr++;
			}
			all->nbr = 0;
			if (cast_plan(all) == true && all->dist > all->t)
			{
				all->dist = all->t;
				clr = cast_light3(all);
			}
			pixel_puts(&clr, all);
			clr = create_color(0.01, 0.01, 0.01, 0);
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

	all.sphnbr = 2;
	all.env = &mlx;
	all.env->mlx = mlx_init();
	all.env->win = mlx_new_window(all.env->mlx, WIDTH, HEIGHT, "RTv1");
	all.env->img = mlx_new_image(all.env->mlx, WIDTH, HEIGHT);
	all.env->data = mlx_get_data_addr(all.env->img, &all.env->bpp,
	&all.env->sl, &all.env->end);
	all.camera = init_cam(0, 0, -(double)WIDTH);
	all.spot = create_spot(-85, 200, -800, 0.1);
	all.spot.clr = create_color(1, 1, 1, 0);
	all.sph[0] = create_sphere(20, -20, -405, 84);
	all.sph[0].clr = create_color(0.196078, 0.803922, 0.196078, 0);
	all.sph[1] = create_sphere(-75, 35, -555, 50);
	all.sph[1].clr = create_color(1, 0.1, 0.0, 0);
	all.plan = create_plan(0, -80, 0);
	all.plan.clr = create_color(0.5, 0.5, 0.5, 1);
	raytracing(&all);
	mlx_put_image_to_window(all.env->mlx, all.env->win, all.env->img, 0, 0);
	mlx_hook(all.env->win, 17, (1L << 17), proper_exit, &all);
	mlx_hook(all.env->win, 2, (1L << 0), key_press, &all);
	mlx_loop(all.env->mlx);
	return (0);
}
