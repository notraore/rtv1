/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <notraore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:07:14 by notraore          #+#    #+#             */
/*   Updated: 2017/10/18 18:25:16 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void	ft_print_err(int argc)
{
	if (argc > 2)
		ft_putendl("The program can only run one scene at once.");
	if (argc < 2)
		ft_putendl("Please. Enter a scene to display");
	if (argc != 2)
		ft_help();
}

void	ft_help(void)
{
	ft_putendl("usage : ./rtv1 [scene]\n");
	ft_putendl("\t\tScene instruction:");
	ft_putendl("First line: widht heigth");
	ft_putstr("second line: number of sphere, ");
	ft_putendl("number of material, number of light");
	ft_putendl("third line: je sais pas encore");
	exit(EXIT_FAILURE);
}
