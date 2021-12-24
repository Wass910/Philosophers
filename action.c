/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:51:53 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/24 18:47:59 by idhiba           ###   ########.fr       */
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
	if (*arg->philo_dead != 1)
	{
		printf("%lu, philo %d has taken a fork\n",
			(arg->current_time - *arg->time), arg->philo_curr);
		printf("%lu, philo %d is eating\n",
			(arg->current_time - *arg->time), arg->philo_curr);
	}
	pthread_mutex_unlock(arg->write);
	ft_usleep(arg->time_to_eat);
}

void	is_sleep_and_think(t_arg *all)
{
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	if (*all->philo_dead != 1)
		printf("%lu, philo %d is sleeping\n",
			(all->current_time - *all->time), all->philo_curr);
	pthread_mutex_unlock(all->write);
	ft_usleep(all->time_to_sleep);
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	if (*all->philo_dead != 1)
		printf("%lu, philo %d is thinking\n",
			(all->current_time - *all->time), all->philo_curr);
	pthread_mutex_unlock(all->write);
}

void	is_dead_norm(unsigned long int curr_time,
	unsigned long int launch_time, t_arg *all)
{
	if (((curr_time - launch_time) - all->lst_eat) > all->time_to_die)
	{
		pthread_mutex_lock(all->write);
		if (*all->philo_dead == 1)
		{	
			pthread_mutex_unlock(all->write);
			pthread_mutex_unlock(&all->eat);
			return ;
		}
		printf("%lu, philo %d is dead\n",
			(curr_time - launch_time), all->philo_curr);
		*all->philo_dead = 1;
		pthread_mutex_unlock(all->write);
		pthread_mutex_unlock(&all->eat);
		return ;
	}
}

int	finish(t_arg *all)
{
	if (all->finish == 1)
	{	
		pthread_mutex_unlock(all->philo_m);
		return (1);
	}
	return (0);
}

void	*is_dead(void *arg)
{
	t_arg				*all;
	unsigned long int	curr_time;
	unsigned long int	launch_time;

	all = (t_arg *)arg;
	launch_time = *all->time;
	while (1)
	{
		usleep(10);
		curr_time = actual_time();
		pthread_mutex_lock(&all->eat);
		if (((curr_time - launch_time) - all->lst_eat) > all->time_to_die)
		{
			is_dead_norm(curr_time, launch_time, all);
			break ;
		}
		pthread_mutex_unlock(&all->eat);
		pthread_mutex_lock(all->philo_m);
		if (finish(all) == 1)
			break ;
		pthread_mutex_unlock(all->philo_m);
	}
	return (NULL);
}
