/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_scal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:12:22 by notraore          #+#    #+#             */
/*   Updated: 2017/10/30 16:46:35 by notraore         ###   ########.fr       */
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


void	vector_normalize(t_v *target)
{
	target->x = target->x / vector_len(target);
	target->y = target->y / vector_len(target);
	target->z = target->z / vector_len(target);
}

double		vector_mult(t_v *base)
{
	return (base->x * base->x + base->y * base->y + base->z * base->z);
}