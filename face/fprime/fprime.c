#include <stdlib.h>
#include <stdio.h>

void		fprime(char *str)
{
	int i = 2;
	int nbr = atoi(str);
	if (nbr == 1)
		printf("1");
	while (i <= nbr)
	{
		if (nbr % i == 0)
		{
			printf("%d", i);
			if (nbr == i)
				return ;
			printf("*");
			nbr = nbr / i;
			i = 1;
		}
	i++;
	}
}

int main(int argc, char **argv)
{
	fprime(argv[1]);
	printf("\n");
	return 0;
}