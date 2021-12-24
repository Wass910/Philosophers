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
		printf("%lu, philo %d has taken a fork\n",(arg->current_time - *arg->time), arg->philo_curr);
		printf("%lu, philo %d is eating\n",(arg->current_time - *arg->time), arg->philo_curr);
	}
	pthread_mutex_unlock(arg->write);
	ft_usleep(arg->time_to_eat);
}

void 	is_sleep_and_think(t_arg *all)
{
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	if (*all->philo_dead != 1)
		printf("%lu, philo %d is sleeping\n", (all->current_time - *all->time), all->philo_curr);
	pthread_mutex_unlock(all->write);
	ft_usleep(all->time_to_sleep);
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	if (*all->philo_dead != 1)
		printf("%lu, philo %d is thinking\n", (all->current_time - *all->time), all->philo_curr);
	pthread_mutex_unlock(all->write);
}

void    *is_dead(void *arg)
{
	t_arg *all;
	// int i = 0;
	unsigned long int curr_time;
	unsigned long int launch_time;

	all = (t_arg *)arg;
	launch_time = *all->time;
	while (1)
	{
		usleep(10);
		curr_time = actual_time();
		//printf("curr time = %lu----- lst_eat = %lu ------ philo %d\n", (curr_time - all->time), *all->lst_eat, all->philo_curr);
		pthread_mutex_lock(&all->eat);
		if (((curr_time - launch_time) - all->lst_eat) > all->time_to_die)
		{
			if (((curr_time - launch_time) - all->lst_eat) > all->time_to_die)
			{
			pthread_mutex_lock(all->write);
				if (*all->philo_dead == 1)
				{	
					pthread_mutex_unlock(all->write);
					pthread_mutex_unlock(&all->eat);
					break ;
				}
			printf("%lu, philo %d is dead\n", (curr_time - launch_time), all->philo_curr);
			*all->philo_dead = 1;
			pthread_mutex_unlock(all->write);
			pthread_mutex_unlock(&all->eat);
			break ;
		}
		}
		pthread_mutex_unlock(&all->eat);
		pthread_mutex_lock(all->philo_m);
		if (all->finish == 1)
		{	
			pthread_mutex_unlock(all->philo_m);
			break ;
		}
		pthread_mutex_unlock(all->philo_m);
	}
	return NULL;
}