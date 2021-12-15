#include "philo.h"

int mail = 0;   

long int		actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
	{	
		printf("Gettimeofday returned -1\n");
		exit(EXIT_FAILURE);
	}
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //temps en millisecondes
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

void    *routine(void *arg)
{
	t_arg *all;
	struct timeval start;
	struct timeval end;

	//sleep(1);
	all = (t_arg *)arg;
	if (all->time == 0)
		all->time = actual_time();
		if (all->current_philo == all->nb_fork)
		{
			pthread_mutex_lock(&all->philo[0].fork);
			pthread_mutex_lock(&all->philo[all->current_philo - 1].fork);
		}
		else
		{
			pthread_mutex_lock(&all->philo[all->current_philo - 1].fork);
			pthread_mutex_lock(&all->philo[all->current_philo].fork);
		}
		all->current_time = actual_time();
		printf("%lu, philo %d is eating\n",(all->current_time - all->time), all->current_philo);
		ft_usleep(all->time_to_eat);
		if (all->current_philo == all->nb_fork)
		{
			pthread_mutex_unlock(&all->philo[0].fork);
			pthread_mutex_unlock(&all->philo[all->current_philo - 1].fork);
		}
		else
		{
			pthread_mutex_unlock(&all->philo[all->current_philo - 1].fork);
			pthread_mutex_unlock(&all->philo[all->current_philo].fork);
		}
		all->current_time = actual_time();
		printf("%lu, philo %d is sleeping\n", (all->current_time - all->time), all->current_philo);
		ft_usleep(all->time_to_sleep);
	return NULL;
}

int	start_threads(t_arg arg, int i)
{
	while(1)
	{
		if (pthread_create(&arg.philo[i - 1].philosopher, NULL, &routine, &arg) != 0)
            exit(EXIT_FAILURE);
	}
	return 0;
}

int loop_philo(t_arg arg_temp)
{   
    int i;
    struct timeval start;
    struct timeval end;
	t_arg arg;
	
	arg = arg_temp;
    i = 1;
    while (i <= arg.nb_fork)
    {
		arg.current_philo = i;
		start_threads(arg, i);
		i++;
        // if (pthread_join(arg.philo[i - 1].philosopher, NULL) != 0)
        //     exit(EXIT_FAILURE);
    }
	while(1);
    return 1;
}

void    print_philo(t_arg arg)
{
	int i = 0;

	while (i < arg.nb_fork)
	{
		printf("----------------------------\n");
		printf("| philo.nb_philo = %d\n", arg.philo[i].nb_philo);
		printf("| philo.current_philo = %d\n",arg.philo[i].current_philo);
		printf("| philo.dead = %d\n", arg.philo[i].philo_dead);
		printf("----------------------------\n");
		i++;
	}
}

void    print_arg(t_arg arg)
{
	printf("----------------------------\n");
	printf("| arg.time_to_eat = %d\n", arg.time_to_eat);
	printf("| arg.time_to_die = %u\n", arg.time_to_die);
	printf("| arg.time_to_sleep = %d\n", arg.time_to_sleep);
	printf("| arg.time = %lu\n", arg.time);
	printf("----------------------------\n");
}

t_arg   init_philo(t_arg arg)
{
	int i;
	int nb_philo = arg.nb_fork;

	i = 1;
	arg.philo = malloc(sizeof(t_philo) * (arg.nb_fork));
	while (i <= arg.nb_fork)
	{
		arg.philo[i - 1].nb_philo = nb_philo;
		arg.philo[i - 1].current_philo = i;
		arg.philo[i - 1].philo_dead = 0;
		pthread_mutex_init(&arg.philo[i - 1].fork, NULL);
		pthread_mutex_init(&arg.philo[i - 1].next_fork, NULL);
		i++;
	}
	return (arg);
}

int init_philo_struct(char **argv)
{   
	t_philo philo;
	t_arg   arg;
	int i =0;

	arg.time = 0;
	arg.nb_fork = ft_atoi(argv[1]);
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	//print_arg(arg);
	arg = init_philo(arg);
	//print_philo(arg);
	loop_philo(arg);
	free(arg.philo);
	return 1;
}

int main(int argc, char **argv)
{
	struct timeval start;
	struct timeval end;
	if (argc != 5)
	{
		exit(EXIT_FAILURE);
	}
	init_philo_struct(argv);
	return 0;
}