/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:30:10 by notraore          #+#    #+#             */
/*   Updated: 2017/11/25 18:42:30 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_atof_suite(char *str, int i, double a, bool neg)
{
	int j;

	j = 0;
	if (str[i] == '.')
	{
		++i;
		while(ft_isdigit(str[i + j]))
			j++;
		if (neg)
			a = a - (double)ft_atoi(str + i) / (pow(10, j));
		else
			a = a + (double)ft_atoi(str + i) / (pow(10, j));
	}
	return (a);
}
double		ft_atof(char *str)
{
	int		i;
	double	a;
	bool	neg;

	i = 0;
	a = 0;
	neg = false;
	while (!ft_isdigit(str[i]) && str[i] != '-')
		i++;
	if (str[i] == '-')
		neg = true;
	a = (double)ft_atoi(str + i);
	while (str[i] != '.' && (ft_isdigit(str[i]) || str[i] == ' ' || str[i] == '-'))
		i++;
	a = ft_atof_suite(str, i, a, neg);
	return (a);
}

int		main(int argc, char **argv)
{
	printf("argv[1] = %f\n", ft_atof(argv[1]));