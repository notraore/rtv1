#include <unistd.h>

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

int			ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void		ft_reverse(char *str)
{
	int len = ft_strlen(str);
	int i = len;
	int flag = 0;

	while (i >= 0)
	{
		if (str[i] == '\v' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == '\f' || str[i] == ' ' || i == 0)
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
		ft_reverse(argv[1]);
	write(1, "\n", 1);
	return 0;
}
