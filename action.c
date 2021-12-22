#include "philo.h"

void	is_eat(t_arg *arg)
{
	arg->current_time = actual_time();
	pthread_mutex_lock(&arg->eat);
	//printf("philo number %d last eat = %lu ok\n", arg->current_philo, (arg->current_time - *arg->time));
	*arg->lst_eat = (arg->current_time - *arg->time);
	pthread_mutex_unlock(&arg->eat);
	pthread_mutex_lock(arg->write);
	if (*arg->philo_dead != 1)
	{
		printf("%lu, philo %d has taken a fork\n",(arg->current_time - *arg->time), *arg->current_philo);
		printf("%lu, philo %d is eating\n",(arg->current_time - *arg->time), *arg->current_philo);
	}
	pthread_mutex_unlock(arg->write);
	ft_usleep(arg->time_to_eat);
}

void 	is_sleep_and_think(t_arg *all)
{
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	if (*all->philo_dead != 1)
		printf("%lu, philo %d is sleeping\n", (all->current_time - *all->time), *all->current_philo);
	pthread_mutex_unlock(all->write);
	ft_usleep(all->time_to_sleep);
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	if (*all->philo_dead != 1)
		printf("%lu, philo %d is thinking\n", (all->current_time - *all->time), *all->current_philo);
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
	ft_usleep(3);
	while (1)
	{
		curr_time = actual_time();
		pthread_mutex_lock(&all->eat);
		if (((curr_time - launch_time) - *all->lst_eat) > all->time_to_die)
		{
			// printf("condition %lu - %lu > %ld = --------------------------------\n",(curr_time - launch_time), *all->lst_eat, all->time_to_die);
			// printf("philo number %d last eat = %lu--------------------------------\n", all->current_philo, *all->lst_eat);
			// printf("philo number %d dead = %lu--------------------------------\n", all->current_philo, (curr_time - launch_time));
			// printf("condition %lu - %lu > %ld = --------------------------------\n",(curr_time - launch_time), *all->lst_eat, all->time_to_die);
			if (*all->philo_dead == 1)
			{	
				pthread_mutex_unlock(&all->eat);
				break ;
			}
			pthread_mutex_lock(all->write);
			printf("%lu, philo %d is dead\n", (curr_time - launch_time), *all->current_philo);
			pthread_mutex_unlock(all->write);
			*all->philo_dead = 1;
			pthread_mutex_unlock(&all->eat);
			break ;
		}
		pthread_mutex_unlock(&all->eat);
		pthread_mutex_lock(&all->finish_m);
		if (all->finish == 1)
		{	
			pthread_mutex_unlock(&all->finish_m);
			break ;
		}
		pthread_mutex_unlock(&all->finish_m);
		ft_usleep(3);
	}
	return NULL;
}



























// void    *is_dead(void *arg)
// {
// 	t_arg *all;
// 	int i = 0;
// 	unsigned long int curr_time;
// 	unsigned long int launch_time;

// 	all = (t_arg *)arg;
// 	launch_time = *all->time;
// 	while (1)
// 	{
// 		usleep(1);
// 		curr_time = actual_time();
// 		pthread_mutex_lock(&all->eat);
// 		if (((curr_time - launch_time) - all->lst_eat) > all->time_to_die)
// 		{
// 			pthread_mutex_lock(all->write);
// 			printf("%lu, philo %d is dead\n", (curr_time - launch_time), *all->current_philo);
// 			pthread_mutex_destroy(all->write);
// 			while (i < all->nb_fork)
// 			{
// 				pthread_mutex_destroy(&all->philo[i].fork);
// 				i++;
// 			}
// 			//pthread_mutex_unlock(&arg->eat);
//             exit(EXIT_FAILURE);
// 		}
// 		pthread_mutex_unlock(&all->eat);
// 		pthread_mutex_lock(&all->finish_m);
// 		if (all->finish == 1)
// 		{	
// 			pthread_mutex_unlock(&all->finish_m);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&all->finish_m);
// 	}
// 	return NULL;
// }