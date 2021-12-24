#include "philo.h"

void    *routine(void *arg)
{
	t_arg all;
	pthread_t dead;
	int next_philo;

	initialize_all(&all, (t_arg *)arg);
	if (all.philo_curr == all.nb_fork)
		next_philo = 0;
	else
		next_philo = all.philo_curr;
	if (all.nb_fork == 1)
	{
		all.current_time = actual_time();
		printf("%lu, philo %d has taken a fork\n",(all.current_time - *all.time), all.philo_curr);
		ft_usleep(all.time_to_die + 1);
		all.current_time = actual_time();
		printf("%lu, philo %d is dead\n", (all.current_time - *all.time), all.philo_curr);
		free(all.time);
		free(all.philo);
		free(all.write);
		free(all.time_m);
		free(all.philo_m);
		free(all.philo_dead);
		free(all.current_philo);
		free(all.finish_eat);
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&dead, NULL, &is_dead, &all) != 0)
       exit(EXIT_FAILURE);
	pthread_detach(dead);
	while (1 && all.have_eat != all.time_each_philo_must_eat)
	{
		if ((all.philo_curr) % 2 == 0)
		{
			pthread_mutex_lock(&all.philo[all.philo_curr - 1].fork);
			//all.philo[all.philo_curr - 1].mutex_open = 1;
			all.current_time = actual_time();
			pthread_mutex_lock(all.write);
			printf("%lu, philo %d has taken a fork\n",(all.current_time - *all.time), all.philo_curr);
			pthread_mutex_unlock(all.write);
			pthread_mutex_lock(&all.philo[next_philo].fork);
			//all.philo[next_philo].mutex_open = 1;
		}
		else
		{
			all.current_time = actual_time();
			pthread_mutex_lock(all.write);
			printf("%lu, philo %d has taken a fork\n",(all.current_time - *all.time), all.philo_curr);
			pthread_mutex_unlock(all.write);
			pthread_mutex_lock(&all.philo[next_philo].fork);
			//all.philo[next_philo].mutex_open = 1;
			pthread_mutex_lock(&all.philo[all.philo_curr - 1].fork);
			//all.philo[all.philo_curr - 1].mutex_open = 1;
		}
		is_eat(&all);
		if (all.time_each_philo_must_eat != -1)
			all.have_eat++;
		pthread_mutex_unlock(&all.philo[next_philo].fork);
		//all.philo[next_philo].mutex_open = 0;
		pthread_mutex_unlock(&all.philo[all.philo_curr - 1].fork);
		//all.philo[all.philo_curr - 1].mutex_open = 0;
		is_sleep_and_think(&all);
	}
	pthread_mutex_lock(all.philo_m);
	all.finish = 1;
	*all.finish_eat = *all.finish_eat + 1;
	if (*all.finish_eat == all.nb_fork)
		*all.finish_eat = -1;
	pthread_mutex_unlock(all.philo_m);
	ft_usleep(20);
	return NULL;
}

int loop_philo(t_arg *arg_temp)
{   
    int i;
	t_arg arg;
	pthread_t philo;
	
    i = 0;
    while (i < arg_temp->nb_fork)
    {
		arg = *arg_temp;
		i++;
		if (pthread_create(&philo, NULL, &routine, &arg) != 0)
            exit(EXIT_FAILURE);
		pthread_detach(philo);
		ft_usleep(2);

    }
	i = 0;
	while (1)
	{
		pthread_mutex_lock(arg.philo_m);
		if (*arg.finish_eat == -1)
		{
			pthread_mutex_unlock(arg.philo_m);
			break ;
		}
		pthread_mutex_unlock(arg.philo_m);
		ft_usleep(30);
	}
	printf("Each philo ate %d time(s)\n", arg.time_each_philo_must_eat);
    return 1;
}

int main(int argc, char **argv)
{
	init_philo_struct(argv, argc);
	return 0;
}