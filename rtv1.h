/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:06:37 by notraore          #+#    #+#             */
/*   Updated: 2017/10/30 16:46:47 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define BLUE 0x0000FF
# define FBLUE 0x00BFFF
# define FGREY 0x424242
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define GREEN 0x00FF00

# include "./libft/libft.h"
# include "./minilibx_macos/mlx.h"
# include <math.h>
# include <time.h>

typedef struct s_v			t_v;
typedef struct s_mlx		t_mlx;
typedef struct s_all		t_all;

struct						s_mlx
{
	int						sl;
	int						bpp;
	int						end;
	int						*data;
	int						clr;
	void					*mlx;
	void					*win;
	void					*img;
};

struct						s_v
{
	int 					x;
	int 					y;
	int 					z;
};

struct 						s_all
{
	t_mlx					*env;
	t_v						*cam;
	t_v 					*ray;
	t_v 					*dir;

	int						sizew;
	int						sizeh;

	int 					i;
	int 					j;
	int						value;
	double					t;
	double					t1;
	double					t2;
	char	 				*line;
	char 					**save;
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
void						vector_div_scal(t_v *targ, double d, t_v *new);
void						vector_mult_scal(t_v *targ, double s, t_v *new);
void						vector_sub_scal(t_v *targ, double s, t_v *new);
void						vector_normalize(t_v *target);
double						vector_mult(t_v *base);
/*
** vector_op.c
*/
void						vector_sub(t_v *start, t_v *end, t_v *new);
void						vector_add(t_v *base, t_v *add, t_v *new);
double						vector_len(t_v *len);
double						vector_colineaire(double a, double b, double c);
double						vector_unitaire(double a, double b);
double						dot_product(t_v *a, t_v *b);

#endif
