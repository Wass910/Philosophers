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

void	is_eat(t_arg *arg)
{
	arg->current_time = actual_time();
	*arg->lst_eat = (arg->current_time - arg->time);
	//printf("philo %d a manger pour la derniere fois mtn a %lu --------\n", *arg->current_philo, *arg->lst_eat);
	pthread_mutex_lock(arg->write);
	printf("%lu, philo %d has taken a fork\n",(arg->current_time - arg->time), *arg->current_philo);
	printf("%lu, philo %d is eating\n",(arg->current_time - arg->time), *arg->current_philo);
	pthread_mutex_unlock(arg->write);
	ft_usleep(arg->time_to_eat);
}

void	is_sleep_and_think(t_arg *all)
{
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	printf("%lu, philo %d is sleeping\n", (all->current_time - all->time), *all->current_philo);
	pthread_mutex_unlock(all->write);
	ft_usleep(all->time_to_sleep);
	all->current_time = actual_time();
	pthread_mutex_lock(all->write);
	printf("%lu, philo %d is thinking\n", (all->current_time - all->time), *all->current_philo);
	pthread_mutex_unlock(all->write);
}

void	initialize_all(t_arg *all, t_arg *arg)
{
	int i;
	
	i = *arg->current_philo;
	all->current_philo = malloc(sizeof(int));
	all->lst_eat = malloc(sizeof(int));
	all->nb_philo = arg->nb_philo;
    all->nb_fork = arg->nb_fork;
    *all->current_philo = i;
    all->philo_dead = arg->philo_dead;
    all->time_to_die = arg->time_to_die;
   	all->current_time = arg->current_time;
    all->time_to_eat = arg->time_to_eat;
    all->time_to_sleep = arg->time_to_sleep;
	if (arg->time == 0)
		arg->time = actual_time();
	*all->lst_eat = 0;
	all->time = arg->time;
	all->write = arg->write;
	all->philo = arg->philo;
	//printf("philo = %d\n", *all->current_philo);
    //all->time_each_philo_must_eat;
}

void    *is_dead(void *arg)
{
	t_arg *all;
	unsigned long int curr_time;

	all = (t_arg *)arg;
	while (1)
	{
		usleep(1);
		curr_time = actual_time();
		//printf("curr time = %lu----- lst_eat = %lu ------ philo %d\n", (curr_time - all->time), *all->lst_eat, *all->current_philo);
		if (((curr_time - all->time) - *all->lst_eat) > all->time_to_die)
		{
			pthread_mutex_lock(all->write);
			//printf("curr time = %lu----- lst_eat = %lu ------ philo %d\n", (curr_time - all->time), *all->lst_eat, *all->current_philo);
			printf("%lu, philo %d is dead\n", (curr_time - all->time), *all->current_philo);
			//pthread_mutex_lock(&all->write);
            exit(EXIT_FAILURE);
		}
	}
	return NULL;
}

void    *routine(void *arg)
{
	t_arg *all;
	pthread_t dead;

	all = malloc(sizeof(t_arg));
	initialize_all(all, (t_arg *)arg);
	// printf("current philo bg = %d \n", *all->current_philo);
	// sleep(1);
	// printf("current philo bg = %d \n", *all->current_philo);
	if (pthread_create(&dead, NULL, &is_dead, all) != 0)
        exit(EXIT_FAILURE);
	while (1)
	{
		pthread_mutex_lock(&all->philo[*all->current_philo - 1].fork);
		all->current_time = actual_time();
		pthread_mutex_lock(all->write);
		printf("%lu, philo %d has taken a fork\n",(all->current_time - all->time), *all->current_philo);
		pthread_mutex_unlock(all->write);
		if (*all->current_philo == all->nb_fork)
			pthread_mutex_lock(&all->philo[0].fork);
		else
			pthread_mutex_lock(&all->philo[*all->current_philo].fork);
		is_eat(all);
		pthread_mutex_unlock(&all->philo[*all->current_philo - 1].fork);
		if (*all->current_philo == all->nb_fork)
			pthread_mutex_unlock(&all->philo[0].fork);
		else
			pthread_mutex_unlock(&all->philo[*all->current_philo].fork);
		is_sleep_and_think(all);
	}
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
		arg->current_philo = malloc(sizeof(int)); 
		i++;
		*arg->current_philo = i;
		//printf("current philo = %d \n", *arg->current_philo);
		if (pthread_create(&arg->philo[i - 1].philosopher, NULL, &routine, arg) != 0)
            exit(EXIT_FAILURE);
		ft_usleep(5);
    }
	i = 1;
	while (i <= arg_temp->nb_fork)
	{
		if (pthread_join(arg->philo[i - 1].philosopher, NULL) != 0)
        	exit(EXIT_FAILURE);
	}
	// while(1);
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
		arg.philo[i - 1].current_philo = i - 1;
		arg.philo[i - 1].philo_dead = 0;
		arg.philo[i - 1].last_eat = 0;
		arg.philo[i - 1].is_eating = 0;
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
	arg.write = malloc(sizeof(pthread_mutex_t));
	arg.nb_fork = ft_atoi(argv[1]);
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(arg.write, NULL);
	//print_arg(arg);
	arg = init_philo(arg);
	//print_philo(arg);
	loop_philo(&arg);
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