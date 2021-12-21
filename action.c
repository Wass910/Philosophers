/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:18:41 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/21 17:24:16 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eat(t_arg *arg)
{
	arg->current_time = actual_time();
	pthread_mutex_lock(&arg->eat);
	arg->lst_eat = (arg->current_time - *arg->time);
	pthread_mutex_unlock(&arg->eat);
	pthread_mutex_lock(arg->write);
	printf("%lu, philo %d has taken a fork\n",(arg->current_time - *arg->time), arg->current_philo);
	printf("%lu, philo %d is eating\n",(arg->current_time - *arg->time), arg->current_philo);
	pthread_mutex_unlock(arg->write);
	ft_usleep(arg->time_to_eat);
}

void 	is_sleep_and_think(t_arg *all)
{
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	printf("%lu, philo %d is sleeping\n", (all->current_time - *all->time), all->current_philo);
	pthread_mutex_unlock(all->write);
	ft_usleep(all->time_to_sleep);
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	printf("%lu, philo %d is thinking\n", (all->current_time - *all->time), all->current_philo);
	pthread_mutex_unlock(all->write);
}

void    *is_dead(void *arg)
{
	t_arg *all;
	//int i = 0;
	unsigned long int curr_time;
	unsigned long int launch_time;

	all = (t_arg *)arg;
	launch_time = *all->time;
	while (1)
	{
		usleep(1);
		curr_time = actual_time();
		pthread_mutex_lock(&all->eat);
		if (((curr_time - launch_time) - all->lst_eat) > all->time_to_die)
		{
			pthread_mutex_lock(all->write);
			if (*all->philo_dead == 1)
			{	
				pthread_mutex_unlock(all->write);
				break ;
			}
			printf("%lu, philo %d is dead\n", (curr_time - launch_time), all->current_philo);
			//pthread_mutex_destroy(all->write);
			// while (i < all->nb_fork)
			// {
			// 	pthread_mutex_destroy(&all->philo[i].fork);
			// 	i++;
			// }
			// free(all->write);
			// free(all->time);
			// free(all->philo);
			// free(all->write);
			// free(all->time);
			// free(all);
			*all->philo_dead = 1;
			pthread_mutex_unlock(all->write);
			pthread_mutex_unlock(&all->eat);
			//pthread_mutex_destroy(all->write);
			break ;
			//exit(EXIT_FAILURE);
		}
		pthread_mutex_unlock(&all->eat);
		pthread_mutex_lock(&all->finish_m);
		if (all->finish == 1)
		{	
			pthread_mutex_unlock(&all->finish_m);
			break ;
		}
		pthread_mutex_unlock(&all->finish_m);
	}
	return NULL;
}