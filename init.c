#include "philo.h"

t_arg	verif_arg(t_arg arg, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{	
		printf("Error, wrong number of argument.\n");
		exit(EXIT_FAILURE);
	}
	if (argc == 6)
		arg.time_each_philo_must_eat = ft_atoi(argv[5]);
	else
		arg.time_each_philo_must_eat = -1;
	return (arg);
}

t_arg   init_philo(t_arg arg)
{
	int i;

	i = 1;
	arg.philo = malloc(sizeof(t_philo) * (arg.nb_fork));
	while (i <= arg.nb_fork)
	{
		arg.philo[i - 1].mutex_open = 0;
		arg.philo[i - 1].current_philo = i - 1;
		arg.philo[i - 1].philo_dead = 0;
		arg.philo[i - 1].last_eat = 0;
		arg.philo[i - 1].eat = 0;
		pthread_mutex_init(&arg.philo[i - 1].fork, NULL);
		i++;
	}
	return (arg);
}

int init_philo_struct(char **argv, int argc)
{   
	t_arg   arg;

	arg.temp = 0;
	arg = verif_arg(arg, argc, argv);
	arg.nb_fork = ft_atoi(argv[1]);
	arg.time = malloc(sizeof(unsigned long int) * arg.nb_fork);
	*arg.time = 0;
	arg.write = malloc(sizeof(pthread_mutex_t) *  arg.nb_fork);
	arg.time_m = malloc(sizeof(pthread_mutex_t) *  arg.nb_fork);
	arg.philo_m = malloc(sizeof(pthread_mutex_t) *  arg.nb_fork);
	arg.finish_eat = malloc(sizeof(int) *  arg.nb_fork);
	arg.current_philo = malloc(sizeof(int) *  arg.nb_fork);
	arg.philo_dead = malloc(sizeof(int) *  arg.nb_fork);
	*arg.finish_eat = 0;
	*arg.current_philo = 1;
	*arg.philo_dead = 0;
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(arg.write, NULL);
	pthread_mutex_init(arg.time_m, NULL);
	pthread_mutex_init(arg.philo_m, NULL);
	arg = init_philo(arg);
	loop_philo(&arg);
	free(arg.philo);
	free(arg.write);
	free(arg.time_m);
	free(arg.philo_m);
	free(arg.time);
	free(arg.philo_dead);
	free(arg.current_philo);
	free(arg.finish_eat);
	return 1;
}

void	initialize_all(t_arg *all, t_arg *arg)
{
	pthread_mutex_lock(arg->philo_m);
	all->philo_curr = *arg->current_philo;
	*arg->current_philo = *arg->current_philo + 1;
	all->current_philo = arg->current_philo;
	pthread_mutex_unlock(arg->philo_m);
	all->nb_philo = arg->nb_philo;
	all->nb_fork = arg->nb_fork;
	all->philo_dead = arg->philo_dead;
	all->time_to_die = arg->time_to_die;
   	all->current_time = arg->current_time;
	all->finish_eat = arg->finish_eat;
	all->time_to_eat = arg->time_to_eat;
	all->time_to_sleep = arg->time_to_sleep;
	all->finish = 0;
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