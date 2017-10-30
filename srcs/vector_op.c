/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:47:33 by notraore          #+#    #+#             */
/*   Updated: 2017/10/30 16:46:48 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		vector_sub(t_v *start, t_v *end, t_v *new)
{
	new->x = end->x - start->x;
	new->y = end->y - start->y;
	new->z = end->z - start->z;
}

void		vector_add(t_v *base, t_v *add, t_v *new)
{
	new->x = base->x + add->x;
	new->y = base->y + add->y;
	new->z = base->z + add->z;
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
	return (sqrtf(pow(len->x, 2) + pow(len->y, 2) + pow(len->z, 2)));
}

double		vector_colineaire(double a, double b, double c)
{
	return (pow(a, 2) + pow(b, 2) + pow(c, 2));
}

double		vector_unitaire(double a, double b)
{
	if (a < 0)
		return (-(sqrt(a) / sqrtf(b)));
	return (sqrt(a) / sqrtf(b));
}
