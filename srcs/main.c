/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:07:14 by notraore          #+#    #+#             */
/*   Updated: 2017/12/02 23:52:41 by nobila           ###   ########.fr       */
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

void		init_lst(t_all *all)
{
	all->o_tmp = all->head;
	all->lght = all->head;
	all->plan = all->head;
	while (all->lght->type != 'L')
		all->lght = all->lght->next;
	while (all->plan->type != 'P')
		all->plan = all->plan->next;
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

bool		cast_plan(t_all *all, t_ray *ray, t_obj *plan)
{
	t_v			o;
	double		a;
	double		b;
	double		s;

	o = vector_sub(&plan->pos, &all->camera.cam_pos);
	a = dot_product(&all->vecdiry, &o);
	b = dot_product(&all->vecdiry, &ray->dir);
	s = -(a / b);
	if (a == 0 || s < 0)
		return (false);
	all->t = s;
	return (true);
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

bool		cast_shadow(t_all *all)
{
	t_obj	*temp;

	temp = all->head;
	while (temp)
	{
		if (cast_sphere(all, &all->shadow, temp) == true)
			return (true);
		temp = temp->next;
	}
	temp = all->head;
	return (false);
}

t_color		cast_light_plan(t_all *all, t_obj *plan, t_obj *light)
{
	t_color		clr;
	t_v			d;
	double		angle;

	all->hit = vector_mult_scal(&all->ray.dir, all->t);
	all->hit = vector_add(&all->ray.pos, &all->hit);
	light->ray.dir = vector_sub(&light->ray.pos, &all->hit);
	light->ray.dir = vector_normalize(&light->ray.dir);
	d = vector_mult_scal(&light->ray.dir, (-1.0));
	angle = dot_product(&d, &all->vecdiry);
	if (angle <= 0)
		return (create_color(0, 0, 0, 0));
	all->shadow.pos = all->hit;
	all->shadow.dir = vector_sub(&light->pos, &all->hit);
	if (cast_shadow(all) == true)
		return (create_color(0, 0, 0, 0));
	int carre = (int)floor(all->hit.x) + (int)floor(all->hit.z);
	if ((carre % 2) == 0)
	{
		clr.r = 0 * light->clr.r * angle;
		clr.g = 0 * light->clr.g * angle;
		clr.b = 0 * light->clr.b * angle;
		return (clr);
	}
	clr.r = plan->clr.r * light->clr.r * angle;
	clr.g = plan->clr.g * light->clr.g * angle;
	clr.b = plan->clr.b * light->clr.b * angle;
	return (clr);
}

void		pixel_puts(t_color *clr, t_all *all)
{
	all->env->data[(all->x + all->y * WIDTH) * 4] = clr->b * 255.0;
	all->env->data[(all->x + all->y * WIDTH) * 4 + 1] = clr->g * 255.0;
	all->env->data[(all->x + all->y * WIDTH) * 4 + 2] = clr->r * 255.0;
	// all->env->data[(all->x + all->y * WIDTH) * 4 + 3] = clr->a * 255.0;
}

void		t_pixel_puts(t_all *all)
{
	all->env->data[(all->x + all->y * WIDTH) * 4] = all->i_tex[(all->x % 1136 + all->y % 295 * WIDTH) * 4];
	all->env->data[(all->x + all->y * WIDTH) * 4 + 1] = all->i_tex[(all->x % 1136 + all->y % 295 * WIDTH) * 4 + 1];
	all->env->data[(all->x + all->y * WIDTH) * 4 + 2] = all->i_tex[(all->x % 1136 + all->y % 295 * WIDTH) * 4 + 2];
	// all->env->data[(all->x + all->y * WIDTH) * 4 + 3] = all->i_tex[(all->x + all->y * WIDTH) * 4 + 3];
}

t_color		cast_light(t_all *all, t_obj *tmp, t_obj *light)
{
	t_color		clr;
	t_v			d;
	// t_v			vp;
	// t_v			vn;
	// t_v			ve;
	// int			u;
	// int			v;
	// double		theta;
	double		angle;
	all->hit = vector_mult_scal(&all->ray.dir, all->t);
	all->hit = vector_add(&all->ray.pos, &all->hit);
	// vn = all->o_tmp->pos;
	// vp = all->o_tmp->pos;
	// ve = all->o_tmp->pos;

	// vn.y += all->o_tmp->r;
	// ve.z -= all->o_tmp->r;
	// vp = vector_sub(&all->o_tmp->pos, &all->hit);
	// vn = vector_normalize(&vn);
	// vp = vector_normalize(&vp);
	// ve = vector_normalize(&ve);
	// double phi = acos(-dot_product(&vn, &vp));
	// v = phi / PI;
	// // printf("phi = %f || v = %d\n", phi, v);
	// theta = (acos(dot_product(&vp, &ve) / sin(phi))) / pow(PI, 2);
	// t_v cross = cross_product(&vn, &ve);
	// if (dot_product(&cross, &vp) > 0)
	// 	u = theta;
	// else
	// 	u = 1 - theta;
	// printf("theta = %f\n", theta);
	all->normal = vector_sub(&tmp->pos, &all->hit);
	all->normal = vector_div_scal(&all->normal, tmp->r);
	light->ray.dir = vector_sub(&light->ray.pos, &all->hit);
	light->ray.dir = vector_normalize(&light->ray.dir);
	d = vector_mult_scal(&light->ray.dir, (-1.0));
	angle = dot_product(&d, &all->normal);
	if (angle <= 0)
		return (create_color(0, 0, 0, 0));
	int carre = (int)floor(all->hit.x) + (int)floor(all->hit.y);
	if ((carre % 2) == 0)
	{
		clr.r = 0 * light->clr.r * angle;
		clr.g = 0 * light->clr.g * angle;
		clr.b = 0 * light->clr.b * angle;
		return (clr);
	}
	clr.r = tmp->clr.r * light->clr.r * angle;
	clr.g = tmp->clr.g * light->clr.g * angle;
	clr.b = tmp->clr.b * light->clr.b * angle;
	return (clr);
}

void	print_tab(t_obj *some)
{
	t_obj	*tmp;

	tmp = some;
	if (tmp)
		while (tmp)
		{
			printf("tmp->type = %c | ", tmp->type);
			printf("tmp->pos.x = %f | ", tmp->pos.x);
			printf("tmp->pos.y = %f | ", tmp->pos.y);
			printf("tmp->pos.z = %f | ", tmp->pos.z);
			printf("tmp->r = %f | ", tmp->r);
			tmp = tmp->next;
		}
}

t_color		get_texture_info(int x, int y, char *tex, t_all *all)
{
	t_color clr;

	clr.r = tex[x + y * all->i_sl];
	return (clr);
}

void		cast_something(t_all *all)
{
	all->clr = create_color(0.01, 0.01, 0.01, 0);
	while (all->o_tmp)
	{
		if (cast_plan(all, &all->ray, all->plan) == true && all->dist > all->t)
		{
			all->dist = all->t;
			all->clr = cast_light_plan(all, all->plan, all->lght);
		}
		if (cast_sphere(all, &all->ray, all->o_tmp) == true && all->dist > all->t)
		{
			all->dist = all->t;
			// all->clr = cast_light(all, all->o_tmp, all->lght);
			// all->clr = get_texture_info(all->x, all->y,  all->i_tex, all);
		}
		all->o_tmp = all->o_tmp->next;
	}
}

void		raytracing(t_all *all)
{
	int			x1;
	int			y1;

	all->y = 0;
	init_lst(all);
	y1 = (HEIGHT / 2);
	while (all->y < HEIGHT)
	{
		all->x = 0;
		x1 = -(WIDTH / 2);
		while (all->x < WIDTH)
		{
			all->dist = 200000;
			all->ray = init_ray(all, x1, y1);
			cast_something(all);
			// if (all->x > 0 && all->x < WIDTH && all->y < HEIGHT && all->y > 0)
			t_pixel_puts(all);
			all->x++;
			x1++;
			all->o_tmp = all->head;
		}
		all->y++;
		y1--;
	}
}

t_obj		*create_plan(char **tmp)
{
	t_obj		*new;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	new->pos = create_vector(ft_atof(tmp[1]), ft_atof(tmp[2]), ft_atof(tmp[3]));
	new->clr = create_color(ft_atof(tmp[4]), ft_atof(tmp[5]), ft_atof(tmp[6]), ft_atof(tmp[7]));
	new->type = 'P';
	new->r = 0;
	return (new);
}


t_obj		*create_sphere(char **tmp)
{
	t_obj	*new;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	new->pos = create_vector(ft_atof(tmp[1]), ft_atof(tmp[2]), ft_atof(tmp[3]));
	new->r = ft_atof(tmp[4]);
	new->clr = create_color(ft_atof(tmp[5]), ft_atof(tmp[6]),
	ft_atof(tmp[7]), ft_atof(tmp[8]));
	new->type = 'S';
	return (new);
}

static void		add_to_list(t_obj **obj, t_obj *new_obj)
{
	t_obj		*tmp;

	if (!obj || !new_obj)
		return ;
	tmp = *obj;
	new_obj->next = NULL;
	if (!tmp)
	{
		*obj = new_obj;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_obj;
}

t_obj		*create_spot(char **tmp)
{
	t_obj	*new;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	new->pos = create_vector(ft_atof(tmp[1]), ft_atof(tmp[2]), ft_atof(tmp[3]));
	new->ray.pos = create_vector(ft_atof(tmp[1]), ft_atof(tmp[2]), ft_atof(tmp[3]));
	new->clr = create_color(ft_atof(tmp[4]), ft_atof(tmp[5]), ft_atof(tmp[6]), ft_atof(tmp[7]));
	new->r = 0;
	new->type = 'L';
	return (new);
}

t_obj		*get_scene(int fd, t_all *all)
{
	int		val;
	t_obj	*new_obj;
	t_obj	*obj;

	obj = NULL;
	while ((val = get_next_line(fd, &all->line)) == 1)
	{
		all->tmp = ft_strsplit(all->line, '\t');

		if (all->tmp[0][0] == 'S')
			new_obj = create_sphere(all->tmp);
		if (all->tmp[0][0] == 'L')
			new_obj = create_spot(all->tmp);
		if (all->tmp[0][0] == 'P')
			new_obj = create_plan(all->tmp);
		add_to_list(&obj, new_obj);
		free_tab(all->tmp);
	}
	if (!obj)
		ft_kill("No scene found, sorry m8.");
	return (obj);
}

int			main(int argc, char **argv)
{
	t_mlx		mlx;
	t_all		*all;
	void		*tex;

	if (argc < 2)
		ft_help();
	all = (t_all *)malloc(sizeof(t_all));
	(!(all->fd = open(argv[1], O_RDONLY)) ? ft_kill("fuck") : 0);
	all->head = get_scene(all->fd, all);
	all->env = &mlx;
	all->env->mlx = mlx_init();
	all->env->win = mlx_new_window(all->env->mlx, WIDTH, HEIGHT, "RTv1");
	all->env->img = mlx_new_image(all->env->mlx, WIDTH, HEIGHT);
	all->env->data = mlx_get_data_addr(all->env->img, &all->env->bpp,
	&all->env->sl, &all->env->end);
	if (!((tex = mlx_xpm_file_to_image(all->env->mlx,
	"./map_texture_11.xpm", &(all->env->sl), &all->env->bpp))))
	ft_kill("Texture error");
	all->i_tex = mlx_get_data_addr(all->env->mlx, &all->i_bpp, &all->i_sl, &all->i_sl);
	all->camera = init_cam(0, 0, -(double)WIDTH);
	raytracing(all);
	mlx_put_image_to_window(all->env->mlx, all->env->win, all->env->img, 0, 0);
	mlx_hook(all->env->win, 17, (1L << 17), proper_exit, &all);
	mlx_hook(all->env->win, 2, (1L << 0), key_press, &all);
	mlx_loop(all->env->mlx);
	return (0);
}