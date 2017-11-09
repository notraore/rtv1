/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_scal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:12:22 by notraore          #+#    #+#             */
/*   Updated: 2017/10/31 14:28:51 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		vector_div_scal(t_v *targ, double d, t_v *new)
{
	new->x = targ->x / d;
	new->y = targ->y / d;
	new->z = targ->z / d;
}

void		vector_mult_scal(t_v *targ, double s, t_v *new)
{
	new->x = targ->x * s;
	new->y = targ->y * s;
	new->z = targ->z * s;
}

void		vector_sub_scal(t_v *targ, double s, t_v *new)
{
	new->x = targ->x - s;
	new->y = targ->y - s;
	new->z = targ->z - s;
}


double		vector_normalize(t_v *target)
{
	double		normalized;

	normalized = vector_len(target);
	target->x = target->x / normalized;
	target->y = target->y / normalized;
	target->z = target->z / normalized;
	return (normalized);
}

double		vector_mult(t_v *base)
{
	return (sqrtf(base->x * base->x + base->y * base->y + base->z * base->z));
}
