/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		set_color(double b, double g, double r)
{
	t_color color;

	color.b = b;
	color.g = g;
	color.r = r;
	return (color);
}

t_color		c_c_add(t_color *a, t_color *b)
{
	t_color	color;

	color.b = sqrt(a->b * a->b + b->b * b->b);
	color.g = sqrt(a->g * a->g + b->g * b->g);
	color.r = sqrt(a->r * a->r + b->r * b->r);
	if (color.b > 1)
		color.b = 1;
	if (color.g > 1)
		color.g = 1;
	if (color.r > 1)
		color.r = 1;
	return (color);
}

t_color		c_double_add(t_color *a, double b)
{
	t_color	color;

	color.b = sqrt(a->b * a->b + b * b);
	color.g = sqrt(a->g * a->g + b * b);
	color.r = sqrt(a->r * a->r + b * b);
	if (color.b > 1)
		color.b = 1;
	if (color.g > 1)
		color.g = 1;
	if (color.r > 1)
		color.r = 1;
	return (color);
}
