/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:47:33 by notraore          #+#    #+#             */
/*   Updated: 2017/10/30 18:02:38 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_v			vector_sub(t_v *start, t_v *end)
{
	t_v		new;

	new.x = end->x - start->x;
	new.y = end->y - start->y;
	new.z = end->z - start->z;
	return (new);
}

t_v			vector_add(t_v *base, t_v *add)
{
	t_v		new;

	new.x = base->x + add->x;
	new.y = base->y + add->y;
	new.z = base->z + add->z;
	return (new);
}

double		dot_product(t_v *a, t_v *b)
{
	double x;
	double y;
	double z;

	x = a->x * b->x;
	y = a->y * b->y;
	z = a->z * b->z;
	return (x + y + z);
}

double		vector_len(t_v *len)
{
	return (sqrt(len->x * len->x + len->y * len->y + len->z * len->z));
}

double		vector_colineaire(double a, double b, double c)
{
	return (a * a + b * b + c * c);
}

double		vector_unitaire(double a, double b)
{
	if (a < 0)
		return (-(sqrt(a) / sqrt(b)));
	return (sqrt(a) / sqrt(b));
}
