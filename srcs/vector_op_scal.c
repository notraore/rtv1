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

t_v			vector_div_scal(t_v *targ, double d)
{
	t_v		new;

	new.x = targ->x / d;
	new.y = targ->y / d;
	new.z = targ->z / d;
	return (new);
}

t_v			vector_mult_scal(t_v *targ, double s)
{
	t_v		new;

	new.x = targ->x * s;
	new.y = targ->y * s;
	new.z = targ->z * s;
	return (new);
}

t_v			vector_sub_scal(t_v *targ, double s)
{
	t_v		new;

	new.x = targ->x - s;
	new.y = targ->y - s;
	new.z = targ->z - s;
	return (new);
}

t_v			vector_normalize(t_v *target)
{
	t_v		new;
	double	normalized;

	new = *target;
	normalized = vector_len(target);
	new.x = new.x / normalized;
	new.y = new.y / normalized;
	new.z = new.z / normalized;
	return (new);
}

double		vector_mult(t_v *base)
{
	return (sqrtf(base->x * base->x + base->y * base->y + base->z * base->z));
}
