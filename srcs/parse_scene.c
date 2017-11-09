// void		parce_scene(int fd, t_all *all)
// {
// 	all->j = 0;
// 	while ((all->value = get_next_line(fd, &(all->line))) == 1)
// 	{
// 		all->save = ft_strsplit(all->line, ' ');
// 		if (all->j == 0)
// 		{
// 			all->sizew = ft_atoi(all->save[0]);
// 			all->sizeh = ft_atoi(all->save[1]);
// 			if (all->sizew > 1920)
// 				all->sizew = 1920;
// 			if (all->sizeh > 1080)
// 				all->sizeh = 1080;
// 			printf("%d\n", all->sizew);
// 			printf("%d\n", all->sizeh);
// 		}
// 		if (all->j == 1)
// 		{
// 			all->nb_sphere = ft_atoi(all->save[1]);
// 			all->nb_mat = ft_atoi(all->save[0]);
// 			all->nb_light = ft_atoi(all->save[2]);

// 			printf("sphere = %d\n", all->nb_sphere);
// 			printf("mat = %d\n", all->nb_mat);
// 			printf("light = %d\n", all->nb_light);
// 		}
// 		all->j++;
// 		free_tab(all->save);
// 		free(all->line);
// 	}
// }