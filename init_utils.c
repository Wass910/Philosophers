/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:42:14 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/24 19:43:06 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_all2(t_arg *all, t_arg *arg)
{
	all->nb_philo = arg->nb_philo;
	all->nb_fork = arg->nb_fork;
	all->philo_dead = arg->philo_dead;
	all->time_to_die = arg->time_to_die;
	all->current_time = arg->current_time;
	all->finish_eat = arg->finish_eat;
	all->time_to_eat = arg->time_to_eat;
	all->time_to_sleep = arg->time_to_sleep;
	all->finish = 0;
}

void	initialize_all(t_arg *all, t_arg *arg)
{
	pthread_mutex_lock(arg->philo_m);
	all->philo_curr = *arg->current_philo;
	*arg->current_philo = *arg->current_philo + 1;
	all->current_philo = arg->current_philo;
	pthread_mutex_unlock(arg->philo_m);
	initialize_all2(all, arg);
	pthread_mutex_lock(arg->time_m);
	if (*arg->time == 0)
		*arg->time = actual_time();
	all->time_m = arg->time_m;
	pthread_mutex_unlock(arg->time_m);
	all->lst_eat = 0;
	all->time = arg->time;
	all->have_eat = 0;
	all->time_each_philo_must_eat = arg->time_each_philo_must_eat;
	all->write = arg->write;
	all->philo = arg->philo;
	all->philo_m = arg->philo_m;
	pthread_mutex_init(&all->eat, NULL);
	pthread_mutex_init(&all->finish_m, NULL);
	pthread_mutex_init(&all->clean_forks, NULL);
}

int	init_next_philo(t_arg all)
{
	int	next_philo;

	if (all.philo_curr == all.nb_fork)
		next_philo = 0;
	else
		next_philo = all.philo_curr;
	return (next_philo);
}

t_arg	init_finish(t_arg all)
{
	pthread_mutex_lock(all.philo_m);
	all.finish = 1;
	*all.finish_eat = *all.finish_eat + 1;
	if (*all.finish_eat == all.nb_fork)
		*all.finish_eat = -1;
	pthread_mutex_unlock(all.philo_m);
	ft_usleep(20);
	return (all);
}
