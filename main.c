#include "philo.h"

void    *routine(void *arg)
{
	t_arg all;
	pthread_t dead;

	initialize_all(&all, (t_arg *)arg);
	if (pthread_create(&dead, NULL, &is_dead, &all) != 0)
       exit(EXIT_FAILURE);
	pthread_detach(dead);
	printf("philo %d is here\n", all.philo_curr);
	while (1 && all.have_eat != all.time_each_philo_must_eat)
	{
		pthread_mutex_lock(&all.philo[all.philo_curr - 1].fork);
		all.current_time = actual_time();
		pthread_mutex_lock(all.write);
		printf("%lu, philo %d has taken a fork\n",(all.current_time - *all.time), all.philo_curr);
		pthread_mutex_unlock(all.write);
		if (all.philo_curr == all.nb_fork)
			pthread_mutex_lock(&all.philo[0].fork);
		else
			pthread_mutex_lock(&all.philo[all.philo_curr].fork);
		is_eat(&all);
		if (all.time_each_philo_must_eat != -1)
			all.have_eat++;
		pthread_mutex_unlock(&all.philo[all.philo_curr - 1].fork);
		if (all.philo_curr == all.nb_fork)
			pthread_mutex_unlock(&all.philo[0].fork);
		else
			pthread_mutex_unlock(&all.philo[all.philo_curr].fork);
		is_sleep_and_think(&all);
		//printf("--------------philo %d have eat %d times---------------------------\n", all.philo_curr, all.time_each_philo_must_eat);
	}
	//printf("-----------------------------------------\n");
	pthread_mutex_lock(all.philo_m);
	//pthread_mutex_lock(&all.finish_m);
	all.finish = 1;
	*all.finish_eat = *all.finish_eat + 1;
	//pthread_mutex_unlock(&all.finish_m);
	pthread_mutex_unlock(all.philo_m);
	while (*all.finish_eat != all.nb_fork - 1);
	*all.finish_eat = -1;
	ft_usleep(20);
	return NULL;
}

int loop_philo(t_arg *arg_temp)
{   
    int i;
	t_arg *arg;
	pthread_t philo;
	
    i = 0;
    while (i < arg_temp->nb_fork)
    {

		arg = malloc(sizeof(t_arg));
		arg = arg_temp;
		i++;
		if (pthread_create(&philo, NULL, &routine, arg) != 0)
            exit(EXIT_FAILURE);
		pthread_detach(philo);
		ft_usleep(2);

    }
	i = 0;
	while (1)
	{
		pthread_mutex_lock(arg->philo_m);
		if (*arg->finish_eat == -1)
		{
			pthread_mutex_unlock(arg->philo_m);
			break ;
		}
		pthread_mutex_unlock(arg->philo_m);
		ft_usleep(30);
	}
	printf("Each philo ate %d time(s)\n", arg->time_each_philo_must_eat);
    return 1;
}

int main(int argc, char **argv)
{
	init_philo_struct(argv, argc);
	return 0;
}