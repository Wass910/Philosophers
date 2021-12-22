#include "philo.h"

void    *routine(void *arg)
{
	t_arg *all;
	pthread_t dead;

	all = malloc(sizeof(t_arg) * 1);
	initialize_all(all, (t_arg *)arg);
	//printf("philo %d is here \n", all->current_philo);
	if (all->nb_fork == 1)
	{
		all->current_time = actual_time();
		printf("%lu, philo %d has taken a fork\n",(all->current_time - *all->time), *all->current_philo);
		ft_usleep(all->time_to_die + 1);
		all->current_time = actual_time();
		printf("%lu, philo %d is dead\n",(all->current_time - *all->time), *all->current_philo);
		*all->philo_dead = 1;
		return NULL ;
	}
	if (pthread_create(&dead, NULL, &is_dead, all) != 0)
       	exit(EXIT_FAILURE);
	pthread_detach(dead);
	while (1 && all->have_eat != all->time_each_philo_must_eat)
	{
		pthread_mutex_lock(all->dead_m);
		if (*all->philo_dead == 1)
		{
			pthread_mutex_unlock(all->dead_m);
			break ;
		}
		pthread_mutex_unlock(all->dead_m);
		pthread_mutex_lock(&all->philo[*all->current_philo - 1].fork);
		pthread_mutex_lock(all->write);
		all->current_time = actual_time();
		pthread_mutex_lock(all->dead_m);
		if (*all->philo_dead != 1)
		{
			pthread_mutex_unlock(all->dead_m);
			printf("%lu, philo %d has taken a fork\n",(all->current_time - *all->time), *all->current_philo);
		}
		pthread_mutex_unlock(all->dead_m);
		pthread_mutex_unlock(all->write);
		if (*all->current_philo == all->nb_fork)
			pthread_mutex_lock(&all->philo[0].fork);
		else
			pthread_mutex_lock(&all->philo[*all->current_philo].fork);
		is_eat(all);
		if (all->time_each_philo_must_eat != -1)
			all->have_eat++;
		pthread_mutex_unlock(&all->philo[*all->current_philo - 1].fork);
		if (*all->current_philo == all->nb_fork)
			pthread_mutex_unlock(&all->philo[0].fork);
		else
			pthread_mutex_unlock(&all->philo[*all->current_philo].fork);
		is_sleep_and_think(all);

	}
	pthread_mutex_lock(&all->finish_m);
	all->finish = 1;
	pthread_mutex_unlock(&all->finish_m);
	ft_usleep(10);
	return NULL;
}

int loop_philo(t_arg *arg_temp)
{   
    int i;
	t_arg *arg;
	
    i = 0;
    while (i < arg_temp->nb_fork)
    {

		arg = malloc(sizeof(t_arg));
		arg = arg_temp;
		pthread_mutex_lock(arg->philo_m);
		i++;
		arg->current_philo = malloc(sizeof(int) * 1);
		*arg->current_philo = i;
		pthread_mutex_unlock(arg->philo_m);
		if (pthread_create(&arg->philo[i - 1].philosopher, NULL, &routine, arg) != 0)
            exit(EXIT_FAILURE);
		ft_usleep(3);
		//pthread_detach(arg->philo[i - 1].philosopher);
    }
	i = 0;
	while (i < arg_temp->nb_fork)
	{
		if (pthread_join(arg->philo[i].philosopher, NULL) != 0)
        	exit(EXIT_FAILURE);
		i++;
	}
	if (arg_temp->time_each_philo_must_eat != -1 && *arg_temp->philo_dead != 1)
		printf("Each philo ate %d time(s)\n", arg->time_each_philo_must_eat);
    return 1;
}

int main(int argc, char **argv)
{
	init_philo_struct(argv, argc);
	return 0;
}