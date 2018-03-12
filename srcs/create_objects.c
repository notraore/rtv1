/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		create_sphere(t_object *object, char *line)
{
	t_sphere	*sphere;
	char		**tab;
	int			i;

	i = 0;
	sphere = (t_sphere*)ft_memalloc(sizeof(t_sphere));
	tab = ft_strsplit(line, ' ');
	i = tab_count(tab);
	if (i != 10)
		ft_kill("Something went wrong with sphere parameters");
	sphere->center = set_vector(ft_atod(tab[1]), ft_atod(tab[2]),
	ft_atod(tab[3]));
	sphere->radius = ft_atod(tab[4]);
	sphere->color = set_color(ft_atod(tab[5]), ft_atod(tab[6]),
	ft_atod(tab[7]));
	sphere->brightness = ft_atod(tab[8]);
	sphere->id = ft_atoi(tab[9]);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	sphere = add_new_sphere(object, sphere);
	free(tab);
}

void		create_cone(t_object *object, char *line)
{
	t_cone		*cone;
	char		**tab;
	int			i;

	cone = (t_cone*)ft_memalloc(sizeof(t_cone));
	tab = ft_strsplit(line, ' ');
	i = tab_count(tab);
	if (i != 13)
		ft_kill("Something went wrong with cone parameters");
	cone->vertex = set_vector(ft_atod(tab[1]), ft_atod(tab[2]),
	ft_atod(tab[3]));
	cone->tangent = ft_atod(tab[4]);
	cone->axis = set_vector(ft_atod(tab[5]), ft_atod(tab[6]),
	ft_atod(tab[7]));
	cone->axis = normalize(&cone->axis);
	cone->color = set_color(ft_atod(tab[8]), ft_atod(tab[9]),
	ft_atod(tab[10]));
	cone->brightness = ft_atod(tab[11]);
	cone->id = ft_atoi(tab[12]);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	cone = add_new_cone(object, cone);
	free(tab);
}

void		create_cylinder(t_object *object, char *line)
{
	t_cylinder	*cylinder;
	char		**tab;
	int			i;

	cylinder = (t_cylinder*)ft_memalloc(sizeof(t_cylinder));
	tab = ft_strsplit(line, ' ');
	i = tab_count(tab);
	if (i != 13)
		ft_kill("Something went wrong with cylinder parameters");
	cylinder->center = set_vector(ft_atod(tab[1]), ft_atod(tab[2]),
	ft_atod(tab[3]));
	cylinder->radius = ft_atod(tab[4]);
	cylinder->axis = set_vector(ft_atod(tab[5]), ft_atod(tab[6]),
	ft_atod(tab[7]));
	cylinder->axis = normalize(&cylinder->axis);
	cylinder->color = set_color(ft_atod(tab[8]), ft_atod(tab[9]),
	ft_atod(tab[10]));
	cylinder->brightness = ft_atod(tab[11]);
	cylinder->id = ft_atoi(tab[12]);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	cylinder = add_new_cylinder(object, cylinder);
	free(tab);
}

void		create_plane(t_object *object, char *line)
{
	t_plane		*plane;
	char		**tab;
	int			i;

	i = 0;
	plane = (t_plane*)ft_memalloc(sizeof(t_plane));
	tab = ft_strsplit(line, ' ');
	i = tab_count(tab);
	if (i != 12)
		ft_kill("Something went wrong with plane parameters");
	plane->point = set_vector(ft_atod(tab[1]), ft_atod(tab[2]),
		ft_atod(tab[3]));
	plane->normal = set_vector(ft_atod(tab[4]), ft_atod(tab[5]),
		ft_atod(tab[6]));
	plane->normal = normalize(&plane->normal);
	plane->color = set_color(ft_atod(tab[7]), ft_atod(tab[8]),
		ft_atod(tab[9]));
	plane->brightness = ft_atod(tab[10]);
	plane->id = ft_atoi(tab[11]);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	plane = add_new_plane(object, plane);
	free(tab);
}

void		create_light(t_object *object, char *line)
{
	t_light		*light;
	char		**tab;
	int			i;

	i = 0;
	light = (t_light*)ft_memalloc(sizeof(t_light));
	tab = ft_strsplit(line, ' ');
	i = tab_count(tab);
	if (i != 8)
		ft_kill("Something went wrong with light parameters");
	light->origin = set_vector(ft_atod(tab[1]), ft_atod(tab[2]),
		ft_atod(tab[3]));
	light->color = set_color(ft_atod(tab[4]), ft_atod(tab[5]),
		ft_atod(tab[6]));
	light->id = ft_atoi(tab[7]);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	light = add_new_light(object, light);
	free(tab);
}
