#include <unistd.h>
#include <stdio.h>

void		ft_putchar(char c)
{
	write(1, &c ,1);
}

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_revstr(char *str)
{
	int i = 0;
	int len = ft_strlen(str);
	int flag = 0;

	i = len;
	while (i >= 0)
	{
		if (str[i] == '\v' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == ' ' || i == 0)
		{
			len = i;
			if (i == 0)
			{
				i--;
				flag = 1;
			}
			while (str[++i] != '\0')
				ft_putchar(str[i]);
			if (flag == 0)
				ft_putchar(' ');
			i = len;
			str[len] = '\0';
		}
		i--;
	}
}


int main(int argc, char **argv)
{
	if (argc == 2)
		ft_revstr(argv[1]);
	ft_putchar('\n');
	return 0;
}