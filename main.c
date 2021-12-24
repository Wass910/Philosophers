/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:49:30 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/24 19:53:13 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_arg *all, int next_philo)
{
	if ((all->philo_curr) % 2 == 0)
	{
		pthread_mutex_lock(&all->philo[all->philo_curr - 1].fork);
		all->current_time = actual_time();
		pthread_mutex_lock(all->write);
		if (*all->philo_dead != 1)
			printf("%lu, philo %d has taken a fork\n",
				(all->current_time - *all->time), all->philo_curr);
		pthread_mutex_unlock(all->write);
		pthread_mutex_lock(&all->philo[next_philo].fork);
	}
	else
	{
		all->current_time = actual_time();
		pthread_mutex_lock(all->write);
		if (*all->philo_dead != 1)
			printf("%lu, philo %d has taken a fork\n",
				(all->current_time - *all->time), all->philo_curr);
		pthread_mutex_unlock(all->write);
		pthread_mutex_lock(&all->philo[next_philo].fork);
		pthread_mutex_lock(&all->philo[all->philo_curr - 1].fork);
	}
}

void	philo_day(t_arg *all, int next_philo)
{
	while (1 && all->have_eat != all->time_each_philo_must_eat)
	{
		pthread_mutex_lock(all->write);
		if (*all->philo_dead == 1)
		{
			pthread_mutex_unlock(all->write);
			break ;
		}
		pthread_mutex_unlock(all->write);
		take_fork(all, next_philo);
		is_eat(all);
		if (all->time_each_philo_must_eat != -1)
			all->have_eat++;
		pthread_mutex_unlock(&all->philo[next_philo].fork);
		pthread_mutex_unlock(&all->philo[all->philo_curr - 1].fork);
		is_sleep_and_think(all);
	}
}

void	*routine(void *arg)
{
	t_arg		all;
	pthread_t	dead;
	int			next_philo;

	initialize_all(&all, (t_arg *)arg);
	next_philo = init_next_philo(all);
	if (one_philo(all) == 1)
		return (NULL);
	if (pthread_create(&dead, NULL, &is_dead, &all) != 0)
		exit(EXIT_FAILURE);
	pthread_detach(dead);
	if ((all.philo_curr) % 2 == 0)
		ft_usleep(5);
	philo_day(&all, next_philo);
	pthread_mutex_lock(all.philo_m);
	all.finish = 1;
	*all.finish_eat = *all.finish_eat + 1;
	if (*all.finish_eat == all.nb_fork)
		*all.finish_eat = -1;
	pthread_mutex_unlock(all.philo_m);
	ft_usleep(20);
	return (NULL);
}

int	loop_philo(t_arg *arg_temp)
{
	int	i;

	i = 0;
	while (i < arg_temp->nb_fork)
	{
		i++;
		if (pthread_create(&arg_temp->philo[i - 1].philosopher,
				NULL, &routine, arg_temp) != 0)
			exit(EXIT_FAILURE);
		ft_usleep(3);
	}
	i = 0;
	while (i < arg_temp->nb_fork)
	{
		if (pthread_join(arg_temp->philo[i].philosopher, NULL) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	if (*arg_temp->philo_dead != 1)
		printf("Each philo ate %d time(s)\n",
			arg_temp->time_each_philo_must_eat);
	return (1);
}

int	main(int argc, char **argv)
{
	init_philo_struct(argv, argc);
	return (0);
}
