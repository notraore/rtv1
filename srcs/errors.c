/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_print_err(int argc)
{
	if (argc > 2)
		ft_putendl("The program can only run one scene at once.");
	if (argc < 2)
		ft_putendl("Please. Enter a scene to display");
	ft_help();
}

void	ft_help(void)
{
	ft_putendl("usage : ./rtv1 [scene]\n");
	ft_putendl("Scene instruction:\n");
	ft_putendl("Scene attributs: width, height, camera position");
	ft_putendl("Objects name");
	ft_putendl("S.sphere, P.plane, CY.cylinder, CO.Cone and L.light\n");
	ft_putendl("Each object as coord and a normalized color attribut");
	ft_putendl("Sphere additionnal attributs : radius");
	ft_putendl("Plane additionnal attributs : normal");
	ft_putendl("Cylinder additionnal attributs : normal, radius, length");
	ft_putendl("Cone additionnal attributs : tangent, length, normal");
	ft_putendl("Vector are set with x, y and z component");
	ft_putendl("Color are set with r, g and b component\n");
	ft_putendl("Each variable must be set like \"name\": \"value\"");
	ft_putendl("Each object must be set like \"object\": {component}");
	exit(EXIT_FAILURE);
}

void	ft_kill(char *text)
{
	ft_putendl(text);
	exit(EXIT_FAILURE);
}

int		tab_count(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
