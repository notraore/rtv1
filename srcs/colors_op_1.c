/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		c_c_mult(t_color *a, t_color *b)
{
	t_color	color;

	color.b = a->b * b->b;
	color.g = a->g * b->g;
	color.r = a->r * b->r;
	return (color);
}

t_color		c_double_mult(t_color *a, double b)
{
	t_color	color;

	color.b = a->b * b;
	color.g = a->g * b;
	color.r = a->r * b;
	return (color);
}

t_color		c_double_div(t_color *a, double b)
{
	t_color	new;

	new.b = a->b / b;
	new.g = a->g / b;
	new.r = a->r / b;
	new.b = new.b > 1 ? 1 : new.b;
	new.g = new.g > 1 ? 1 : new.g;
	new.r = new.r > 1 ? 1 : new.r;
	return (new);
}

void		print_color(t_color *color, t_datas *d, int x, int y)
{
	if ((x >= 0 && x < d->window_width) && (y >= 0 && y < d->window_height))
	{
		d->mlx.data[(x + y * d->window_width) * 4 + 0] = color->b * 255;
		d->mlx.data[(x + y * d->window_width) * 4 + 1] = color->g * 255;
		d->mlx.data[(x + y * d->window_width) * 4 + 2] = color->r * 255;
	}
}
