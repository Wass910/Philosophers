#include "philo.h"

void    *routine(void *arg)
{
	t_arg all;
	//t_arg *death;
	pthread_t dead;

	initialize_all(&all, (t_arg *)arg);
	//free(arg);
	if (pthread_create(&dead, NULL, &is_dead, &all) != 0)
       exit(EXIT_FAILURE);
	pthread_detach(dead);
	while (1 && all.have_eat != all.time_each_philo_must_eat)
	{
		//if (*all.philo_dead == 1)
		//	break ;
		pthread_mutex_lock(&all.philo[all.current_philo - 1].fork);
		all.current_time = actual_time();
		pthread_mutex_lock(all.write);
		if (*all.philo_dead == 1)
		{	
				pthread_mutex_unlock(all.write);
				break ;
		}
		printf("%lu, philo %d has taken a fork\n",(all.current_time - *all.time), all.current_philo);
		pthread_mutex_unlock(all.write);
		if (all.current_philo == all.nb_fork)
			pthread_mutex_lock(&all.philo[0].fork);
		else
			pthread_mutex_lock(&all.philo[all.current_philo].fork);
		if (*all.philo_dead == 0)
			is_eat(&all);
		pthread_mutex_lock(all.write);
		//printf("philo %d dies is %d\n",all.current_philo, *all.philo_dead);
		if (*all.philo_dead == 1)
		{	
			pthread_mutex_unlock(&all.philo[all.current_philo - 1].fork);
			if (all.current_philo == all.nb_fork)
				pthread_mutex_unlock(&all.philo[0].fork);
			else
				pthread_mutex_unlock(&all.philo[all.current_philo].fork);
			pthread_mutex_unlock(all.write);
			break ;
		}
		pthread_mutex_unlock(all.write);
		pthread_mutex_unlock(&all.philo[all.current_philo - 1].fork);
		if (all.current_philo == all.nb_fork)
			pthread_mutex_unlock(&all.philo[0].fork);
		else
			pthread_mutex_unlock(&all.philo[all.current_philo].fork);
		if (all.time_each_philo_must_eat != -1)
			all.have_eat++;
		is_sleep_and_think(&all);
	}
	printf("philo %d\n",all.current_philo);
	pthread_mutex_lock(&all.finish_m);
	all.finish = 1;
	pthread_mutex_unlock(&all.finish_m);
	ft_usleep(3);
	//free(all);
	return NULL;
}


int loop_philo(t_arg *arg_temp)
{   
    int i;
	t_arg *arg;
	
    i = 0;
    while (i < arg_temp->nb_fork)
    {

		//arg = malloc(sizeof(t_arg) * 1);
		arg = arg_temp;
		i++;
		pthread_mutex_lock(&arg->philo_m);
		arg->current_philo = i;
		pthread_mutex_unlock(&arg->philo_m);
		if (pthread_create(&arg->philo[i - 1].philosopher, NULL, &routine, arg) != 0)
            exit(EXIT_FAILURE);
		//pthread_detach(arg->philo[i - 1].philosopher);
		ft_usleep(5);
		//free(arg);
    }
	i = 0;
	while (i < arg_temp->nb_fork)
	{
		if (pthread_join(arg->philo[i].philosopher, NULL) != 0)
          	exit(EXIT_FAILURE);
		i++;
	}
	pthread_mutex_destroy(arg_temp->write);
	pthread_mutex_destroy(&arg_temp->time_m);
	pthread_mutex_destroy(&arg_temp->philo_m);
	free(arg_temp->time);
	if (arg_temp->time_each_philo_must_eat != -1)
		printf("Each philo ate %d time(s)\n", arg->time_each_philo_must_eat);
    return 1;
}

int main(int argc, char **argv)
{
	init_philo_struct(argv, argc);
	return 0;
}