/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:47:56 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/24 19:53:20 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_alpha(char *str)
{
	int	i;

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
	return (nb);
}

int	one_philo(t_arg all)
{
	if (all.nb_fork != 1)
		return (0);
	*all.philo_dead = 1;
	all.current_time = actual_time();
	printf("%lu, philo %d has taken a fork\n",
		(all.current_time - *all.time), all.philo_curr);
	ft_usleep(all.time_to_die + 1);
	all.current_time = actual_time();
	printf("%lu, philo %d is dead\n",
		(all.current_time - *all.time), all.philo_curr);
	return (1);
}
