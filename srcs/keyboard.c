/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:07:14 by notraore          #+#    #+#             */
/*   Updated: 2017/10/25 18:36:46 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int			proper_exit(t_all *all)
{
	(void)all;
	// mlx_destroy_image(all->env->mlx, all->env->img);
	exit(EXIT_SUCCESS);
	return (0);
}

int			key_press(int keycode, t_all *all)
{
	if (keycode == 53)
		proper_exit(all);
	printf("keycode = %d\n", keycode);
	return (0);
}
