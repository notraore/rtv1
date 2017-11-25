/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:07:14 by notraore          #+#    #+#             */
/*   Updated: 2017/11/25 23:49:17 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

// static void			ft_last_fd(t_sph **file, int fd)
// {
// 	t_sph *tmp;

// 	tmp = *file;
// 	if (!tmp)
// 		*file = ft_create_fd(fd);
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = ft_create_fd(fd);
// 	}
// }

t_v			create_vector(double x, double y, double z)
{
	t_v			ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_v			create_default_vector(void)
{
	t_v		new;

	new.x = 0;
	new.y = 0;
	new.z = 0;

	return (new);
}

t_cam		init_cam(double x, double y, double z)
{
	t_cam		cam;

	cam.cam_pos = create_vector(x, y, z);
	cam.vp = create_default_vector();
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

	all->vecdirx.x = 1;
	all->vecdirx.y = 0;
	all->vecdirx.z = 0;

	all->vecdiry.x = 0;
	all->vecdiry.y = 1;
	all->vecdiry.z = 0;

	all->vecdirz.x = 0;
	all->vecdirz.y = 0;
	all->vecdirz.z = 1;
	return (ray);
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


bool		cast_sphere(t_all *all, t_ray *ray, t_obj *obj)
{
	double		a;
	double		b;
	double		c;
	t_v			o;

	o = vector_sub(&obj->pos, &ray->pos);
	a = dot_product(&ray->dir, &ray->dir);
	b = 2 * dot_product(&ray->dir, &o);
	c = dot_product(&o, &o) - obj->r * obj->r;
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

// bool		cast_cyl(t_all *all, t_ray *ray, t_cyl *cyl)
// {
// 	double		a;
// 	double		b;
// 	double		c;
// 	t_v			o;

// 	// all->normal = vector_sub(&ray->dir, &cyl->pos);

// 	o = vector_sub(&cyl->pos, &ray->pos);
// 	a = dot_product(&ray->dir, &ray->dir) - pow(dot_product(&ray->dir, &all->vecdiry), 2);

// 	b = 2 * dot_product(&ray->pos, &o) - (dot_product(&ray->dir, &all->vecdiry)) * (dot_product(&o, &all->vecdiry));

// 	c = dot_product(&o, &o) - pow(dot_product(&o, &all->vecdiry), 2) - 50 * 50;

// 	all->delta = b * b - 4 * a * c;
// 	if (all->delta < 0)
// 		return (false);
// 	if (all->delta == 0)
// 		all->delta = -b;
// 	if (all->delta > 0)
// 	{
// 		all->t1 = (-b + sqrt(all->delta)) / (2 * a);
// 		all->t2 = (-b - sqrt(all->delta)) / (2 * a);
// 		all->t = all->t1 >= all->t2 ? all->t2 : all->t1;
// 		return (true);
// 	}
// 	return (false);
// }

// t_plan		create_plan(char **tmp)
// {
// 	t_plan		plan;

// 	plan.normal = create_vector(0, 1, 0);
// 	plan.pos = create_vector(x, y, z);
// 	return (plan);
// }

// bool		cast_plan(t_all *all)
// {
// 	t_v			o;
// 	double		a;
// 	double		b;
// 	double		s;

// 	o = vector_sub(&all->plan.pos, &all->camera.cam_pos);
// 	a = dot_product(&all->plan.normal, &o);
// 	b = dot_product(&all->plan.normal, &all->ray.dir);
// 	s = -(a / b);
// 	if (a == 0 || s < 0)
// 		return (false);
// 	all->t = s;
// 	return (true);
// }

// t_spot		create_spot(double x, double y, double z, double intens)
// {
// 	t_spot	spot;

// 	spot.pos = create_vector(x, y, z);
// 	spot.ray.pos = create_vector(x, y, z);
// 	spot.intens = intens;
// 	return (spot);
// }


t_color		cast_light(t_all *all)
{
	t_color		clr;
	t_v			d;
	double		angle;

	all->hit = vector_mult_scal(&all->ray.dir, all->t);
	all->hit = vector_add(&all->ray.pos, &all->hit);
	all->normal = vector_sub(&all->obj->pos, &all->hit);
	all->normal = vector_div_scal(&all->normal, all->obj->r);
	all->spot.ray.dir = vector_sub(&all->spot.pos, &all->hit);
	all->spot.ray.dir = vector_normalize(&all->spot.ray.dir);
	d = vector_mult_scal(&all->spot.ray.dir, (-1.0));
	angle = dot_product(&d, &all->normal);
	if (angle <= 0)
		return (create_color(0, 0, 0, 0));
	clr.r = all->obj->clr.r * all->spot.clr.r * angle;
	clr.g = all->obj->clr.g * all->spot.clr.g * angle;
	clr.b = all->obj->clr.b * all->spot.clr.b * angle;
	return (clr);
}

// t_color		cast_light2(t_all *all)
// {
// 	t_color		clr;
// 	t_v			d;
// 	double		angle;

// 	all->hit = vector_mult_scal(&all->ray.dir, all->t);
// 	all->hit = vector_add(&all->ray.pos, &all->hit);
// 	all->normal = vector_sub(&all->cyl.pos, &all->hit);
// 	all->normal = vector_div_scal(&all->normal, -1);
// 	all->spot.ray.dir = vector_sub(&all->spot.pos, &all->hit);
// 	all->spot.ray.dir = vector_normalize(&all->spot.ray.dir);
// 	d = vector_mult_scal(&all->spot.ray.dir, (-1.0));
// 	angle = dot_product(&d, &all->normal);
// 	if (angle <= 0)
// 		return (create_color(0, 0, 0, 0));
// 	clr.r = all->cyl.clr.r * all->spot.clr.r * angle;
// 	clr.g = all->cyl.clr.g * all->spot.clr.g * angle;
// 	clr.b = all->cyl.clr.b * all->spot.clr.b * angle;
// 	return (clr);
// }

// t_color		cast_light3(t_all *all)
// {
// 	t_color		clr;
// 	t_v			d;
// 	double		angle;

// 	all->hit = vector_mult_scal(&all->ray.dir, all->t);
// 	all->hit = vector_add(&all->ray.pos, &all->hit);
// 	all->spot.ray.dir = vector_sub(&all->spot.pos, &all->hit);
// 	all->spot.ray.dir = vector_normalize(&all->spot.ray.dir);
// 	d = vector_mult_scal(&all->spot.ray.dir, (-1.0));
// 	angle = dot_product(&d, &all->plan.normal);
// 	if (angle <= 0)
// 		return (create_color(0, 0, 0, 0));
// 	all->shadow.dir = vector_sub(&all->hit, &all->spot.pos);
// 	all->shadow.pos = all->hit;
// 	if (cast_sphere(all, &all->shadow, &all->sph) == true)
// 		return (create_color(0, 0, 0, 0));
// 	clr.r = all->plan.clr.r * all->spot.clr.r * angle;
// 	clr.g = all->plan.clr.g * all->spot.clr.g * angle;
// 	clr.b = all->plan.clr.b * all->spot.clr.b * angle;
// 	return (clr);
// }

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
	while (all->y < HEIGHT)
	{
		all->x = 0;
		x1 = -(WIDTH / 2);
		while (all->x < WIDTH)
		{
			all->dist = 20000;
			all->ray = init_ray(all, x1, y1);
			if (cast_sphere(all, &all->ray, all->obj) == true && all->dist > all->t)
			{	
				all->dist = all->t;
				clr = cast_light(all);
			}
			pixel_puts(&clr, all);
			clr = create_color(0.09, 0.09, 0.09, 0);
			all->x++;
			x1++;
		}
		all->y++;
		y1--;
	}
}

// static void			ft_last_fd(t_stock **file, int fd)
// {
// 	t_stock *tmp;

// 	tmp = *file;
// 	if (!tmp)
// 		*file = ft_create_fd(fd);
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = ft_create_fd(fd);
// 	}
// }
void		create_sphere(char **tmp, t_obj *ref)
{
	ref->pos = create_vector(ft_atof(tmp[1]), ft_atof(tmp[2]), ft_atof(tmp[3]));
	ref->r = ft_atof(tmp[4]);
	ref->clr = create_color(ft_atof(tmp[5]), ft_atof(tmp[6]),
	ft_atof(tmp[6]), ft_atof(tmp[7]));
	ref->id = ft_atoi(tmp[8]);
	ref->type = 'S';
}

t_sll		*create_sll(t_obj *content)
{
	t_sll	*sll;

	if (!(sll = malloc(sizeof(t_sll))))
		return (NULL);
	sll->obj_lst = content;
	sll->next = NULL;
	return (sll);
}

void		add_to_list(t_sll **all_obj, t_sll *new_sll)
{
	t_sll		*tmp;
//*****************************************Segfault ici**********************************************//
	if (!(tmp = *all_obj))
		ft_kill("error assigation");
	if (!(*all_obj))
		*all_obj = new_sll;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		new_sll->next = NULL;
		tmp->next = new_sll;
	}
}

t_obj		*create_obj(t_obj *ref)
{
	t_obj	*obj;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	obj->type = ref->type;
	obj->pos = ref->pos;
	obj->clr = ref->clr;
	obj->id = ref->id;
	obj->r = ref->r;
	return (obj);
}

void		get_info(char **tmp, t_obj *ref)
{
	bzero(ref, sizeof(t_obj));
	//fonction() de check des veleurs selon l'objet;
	if (tmp[0][0] == 'S')
		create_sphere(tmp, ref);
}

void		get_scene(int fd, t_all *all)
{
	int		val;
	t_obj	ref;
	t_obj	*new_obj;
	t_sll	**all_obj;
	t_sll	*new_sll;

	all_obj = NULL;
	while ((val = get_next_line(fd, &all->line)) == 1)
	{
		all->tmp = ft_strsplit(all->line, '\t');
		get_info(all->tmp, &ref);
		if (all->tmp[0][0] == 'S')
		{
			new_obj = create_obj(&ref);
			new_sll = create_sll(new_obj);
			printf("%f\n", new_obj->r);
			add_to_list(all_obj, new_sll);
		}
		// free_tab(all->tmp);
	}
}

int			main(int argc, char **argv)
{
	t_mlx		mlx;
	t_all		*all;

	if (argc < 2)
		ft_kill("no arguments");
	all = (t_all *)malloc(sizeof(t_all));
	all->env = &mlx;
	all->env->mlx = mlx_init();
	all->env->win = mlx_new_window(all->env->mlx, WIDTH, HEIGHT, "RTv1");
	all->env->img = mlx_new_image(all->env->mlx, WIDTH, HEIGHT);
	all->env->data = mlx_get_data_addr(all->env->img, &all->env->bpp,
	&all->env->sl, &all->env->end);
	if (!(all->fd = open(argv[1], O_RDONLY)))
		ft_kill("fd error");
	all->camera = init_cam(0, 0, -(double)WIDTH);
	get_scene(all->fd, all);
	// all->spot = create_spot(227, 290, -150, 0.1);
	// all->spot.clr = create_color(1, 1, 1, 0);
	// all->sph = create_sphere(0, 50, 200);
	// all->plan = create_plan(0, -80, 0);
	// all->plan.clr = create_color(0.5, 0.5, 0.5, 1);
	raytracing(all);
	mlx_put_image_to_window(all->env->mlx, all->env->win, all->env->img, 0, 0);
	mlx_hook(all->env->win, 17, (1L << 17), proper_exit, &all);
	mlx_hook(all->env->win, 2, (1L << 0), key_press, &all);
	mlx_loop(all->env->mlx);
	return (0);
}