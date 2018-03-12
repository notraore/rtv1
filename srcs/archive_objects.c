/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_sphere	*add_new_sphere(t_object *object, t_sphere *new_sphere)
{
	t_sphere	*tmp;

	tmp = object->start_sphere;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sphere;
		new_sphere->next = NULL;
	}
	else
		object->start_sphere = new_sphere;
	return (tmp);
}

t_cone		*add_new_cone(t_object *object, t_cone *new_cone)
{
	t_cone	*tmp;

	tmp = object->start_cone;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cone;
		new_cone->next = NULL;
	}
	else
		object->start_cone = new_cone;
	return (tmp);
}

t_cylinder	*add_new_cylinder(t_object *object, t_cylinder *new_cylinder)
{
	t_cylinder	*tmp;

	tmp = object->start_cylinder;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cylinder;
		new_cylinder->next = NULL;
	}
	else
		object->start_cylinder = new_cylinder;
	return (tmp);
}

t_plane		*add_new_plane(t_object *object, t_plane *new_plane)
{
	t_plane		*tmp;

	tmp = object->start_plane;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_plane;
		new_plane->next = NULL;
	}
	else
		object->start_plane = new_plane;
	return (tmp);
}

t_light		*add_new_light(t_object *object, t_light *new_light)
{
	t_light		*tmp;

	tmp = object->start_light;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
		new_light->next = NULL;
	}
	else
		object->start_light = new_light;
	return (tmp);
}
