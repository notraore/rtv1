/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:06:37 by notraore          #+#    #+#             */
/*   Updated: 2017/11/12 19:10:28 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WIDTH 1000
# define HEIGHT 1000

# define BLUE 0x0099FF
# define FBLUE 0x00BFFF
# define GREY 0x424242
# define RED 0xFF0000
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define GREEN 0x00FF00

# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <time.h>

typedef struct s_v			t_v;
typedef struct s_mlx		t_mlx;
typedef struct s_all		t_all;
typedef struct s_ray		t_ray;
typedef struct s_sph		t_sph;
typedef struct s_cam		t_cam;
typedef struct s_spot		t_spot;
typedef struct s_plan		t_plan;
typedef struct s_color		t_color;

struct						s_mlx
{
	int						sl;
	int						bpp;
	int						end;
	char					*data;
	void					*mlx;
	void					*win;
	void					*img;
};

struct						s_v
{
	double					x;
	double					y;
	double					z;
};

struct						s_ray
{
	t_v						pos;
	t_v						dir;
	double					distance;
};

struct						s_color
{
	double					r;
	double					g;
	double					b;
	double					a;
};

struct						s_sph
{
	t_v						pos;
	t_color					clr;
	double					r;
};

struct						s_spot
{
	t_v						pos;
	t_ray					ray;
	t_color					clr;
	double					intens;
	int						color;

};

struct						s_plan
{
	t_v						pos;
	t_color					clr;
	t_v						normal;
	t_v						plan_cam;
};

struct						s_cam
{
	t_v						cam_pos;
	t_v						vp;
};

struct						s_all
{
	t_v						normal;
	t_v						hit;
	t_mlx					*env;
	t_cam					camera;
	t_ray					ray;
	t_ray					shadow;
	t_plan					plan;
	t_sph					sph[20];
	t_spot					spot;

	int						x;
	int						y;
	size_t					sphnbr;
	size_t					nbr;
	double					t;
	double					t1;
	double					dist;
	double					t2;
	double					d;
	double					delta;
};

/*
** Keyboard.c
*/
int							proper_exit(t_all *all);
int							key_press(int keycode, t_all *all);

/*
**error.c
*/
void						ft_print_err(int argc);
void						ft_help(void);
/*
**vector_op_scal.c
*/
t_v							vector_div_scal(t_v *targ, double d);
t_v							vector_mult_scal(t_v *targ, double s);
t_v							vector_sub_scal(t_v *targ, double s);
t_v							vector_normalize(t_v *target);
double						vector_mult(t_v *base);
/*
** vector_op.c
*/
t_v							vector_sub(t_v *start, t_v *end);
t_v							vector_add(t_v *base, t_v *add);
double						vector_len(t_v *len);
double						vector_colineaire(double a, double b, double c);
double						vector_unitaire(double a, double b);
double						dot_product(t_v *a, t_v *b);

#endif
