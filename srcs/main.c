/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:07:14 by notraore          #+#    #+#             */
/*   Updated: 2017/10/30 16:47:55 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void	ft_init_all(t_all *all)
{
	all->sizew = 600;
	all->sizeh = 600;
	all->cam->x = all->sizew / 2;
	all->cam->y = all->sizeh / 2;
	all->cam->z = -200.0;
	all->dir->x = 0;
	all->dir->y = 0;
	all->dir->z = 0;
	all->t = 0;
 }

double div_lilnbr(double a, double b)
{
	return (a / b);
}

t_v		init_obj_pos(double x, double y, double z)
{
	t_v c;

	c.x = x;
	c.y = y;
	c.z = z;
	return (c);
}

void	sphere_calc(t_v *abc, t_v *sph, t_v *dir, t_v *org)
{
	abc->x = vector_mult(dir);
	abc->y = 2 * (dir->x * (org->x - sph->x) + dir->y * (org->y - sph->y)
	+ dir->z * (org->z - sph->z));
	abc->z = pow(org->x - sph->x, 2) + pow(org->y - sph->y, 2) + pow(org->z - sph->z, 2) - 5 * 5;
	printf("x = %d || y = %d || z = %d\n", abc->x, abc->y, abc->z);
}

void	raytracing(t_all *all)
{
	t_v i;
	t_v rray;
	t_v	sph;
	t_v abc;

	i.y = 0;
	vector_normalize(all->cam);
	vector_normalize(&rray);
	sph = init_obj_pos(all->sizew / 2, all->sizeh / 2, 200);
	printf("sphnx = %d || sphnx = %d || sphnx = %d\n", sph.x, sph.y, sph.z);
	while (i.y <= all->sizeh)
	{
		i.x = 0;
		while (i.x <= all->sizew)
		{
			vector_sub(all->cam, &i, &rray);
			sphere_calc(&abc, &sph, &i, all->cam);
			double delta = abc.y * abc.y - 4 * abc.x * abc.z;
			all->t1 = (-abc.y + sqrt(delta)) / (2 * abc.x);
			all->t2 = (-abc.y - sqrt(delta)) / (2 * abc.x);
			all->t = all->t1 > all->t2 ? all->t2 : all->t1;
			vector_mult_scal(&rray, all->t, &rray);
			printf("delta == %f\n", delta);
			if (delta > 0)
				all->env->data[i.x + i.y * all->sizew] = RED;
			i.x++;
		}
		i.y++;
	}
}

int		main(int argc, char **argv)
{
	t_mlx		mlx;
	t_all		all;
	(void)argc;
	(void)argv;
	t_v			c;
	t_v 		r;
	t_v 		d;

	all.cam = &c;
	all.ray = &r;
	all.dir = &d;
	all.env = &mlx;
	ft_init_all(&all);
	all.env->mlx = mlx_init();
	all.env->win = mlx_new_window(all.env->mlx, all.sizew, all.sizeh, "RTv1");
	all.env->img = mlx_new_image(all.env->mlx, all.sizew, all.sizeh);
	all.env->data = (int *)mlx_get_data_addr(all.env->img, &all.env->bpp,
	&all.env->sl, &all.env->end);
	raytracing(&all);
	mlx_put_image_to_window(all.env->mlx, all.env->win, all.env->img, 0, 0);
	mlx_hook(all.env->win, 17, (1L << 17), proper_exit, &all);
	mlx_hook(all.env->win, 2, (1L << 0), key_press, &all);
	mlx_loop(all.env->mlx);
	return (0);
}
