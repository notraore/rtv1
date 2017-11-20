/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:07:14 by notraore          #+#    #+#             */
/*   Updated: 2017/10/19 11:23:37 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		parce_scene(int fd, t_all *all)
{
	all->j = 0;
	while ((all->value = get_next_line(fd, &(all->line))) == 1)
	{
		all->save = ft_strsplit(all->line, ' ');
		if (all->j == 0)
		{
			all->sizew = ft_atoi(all->save[0]);
			all->sizeh = ft_atoi(all->save[1]);
			if (all->sizew > 1920)
				all->sizew = 1920;
			if (all->sizeh > 1080)
				all->sizeh = 1080;
		}
		if (all->j == 1)
		{
			all->nb_sphere = ft_atoi(all->save[1]);
			all->nb_mat = ft_atoi(all->save[0]);
			all->nb_light = ft_atoi(all->save[2]);
		}
		all->j++;
		free_tab(all->save);
		free(all->line);
	}
}
