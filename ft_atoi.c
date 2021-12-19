#include "philo.h"

void is_alpha(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Invalid argument.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}


int	ft_atoi(char *str)
{
	int			i;
	long int	nb;

	nb = 0;
	i = 0;
	is_alpha(str);
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (nb == 0 || nb > INT_MAX)
	{
		printf("Invalid argument.\n");
		exit(EXIT_FAILURE);
	}
	return (nb );
}