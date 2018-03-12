/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 19:50:51 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		create_environment(t_datas *d, char *line)
{
	char		**tab_line;
	int			i;

	tab_line = ft_strsplit(line, ' ');
	if (ft_atod(tab_line[1]) > 1600 || ft_atod(tab_line[1]) < 600)
		ft_kill("Bad window width");
	if (ft_atod(tab_line[2]) > 1200 || ft_atod(tab_line[2]) < 400)
		ft_kill("Bad window height");
	d->window_width = ft_atod(tab_line[1]);
	d->window_height = ft_atod(tab_line[2]);
	d->camera.origin = set_vector(ft_atod(tab_line[3]),
		ft_atod(tab_line[4]), ft_atod(tab_line[5]));
	i = 0;
	while (tab_line[i])
		free(tab_line[i++]);
	free(tab_line);
}

void		open_close(char *src_file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(src_file, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (line)
			free(line);
		i++;
	}
	close(fd);
	if (!(i))
		ft_kill("Bad file. Please enter a valid scene to read.");
}

void		the_one(char *line, t_datas *d, t_object *object)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'E' && line[i + 1] == 'N')
			create_environment(d, line);
		else if (line[i] == 'S' && line[i + 1] == 'P')
			create_sphere(object, line);
		else if (line[i] == 'C' && line[i + 1] == 'Y')
			create_cylinder(object, line);
		else if (line[i] == 'C' && line[i + 1] == 'O')
			create_cone(object, line);
		else if (line[i] == 'P' && line[i + 1] == 'L')
			create_plane(object, line);
		else if (line[i] == 'L' && line[i + 1] == 'I')
			create_light(object, line);
		i++;
	}
}

int			parsing(t_datas *d, t_object *object, char *src_file)
{
	char	*line;
	int		fd;

	open_close(src_file);
	if (!(fd = open(src_file, O_RDONLY)))
		ft_kill("fd error");
	while ((get_next_line(fd, &line) == 1))
	{
		the_one(line, d, object);
		if (line)
			free(line);
	}
	close(fd);
	return (1);
}
