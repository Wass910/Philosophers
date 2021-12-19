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
	int nb_philo = arg.nb_fork;

	i = 1;
	arg.philo = malloc(sizeof(t_philo) * (arg.nb_fork));
	while (i <= arg.nb_fork)
	{
		arg.philo[i - 1].nb_philo = nb_philo;
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
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(arg.write, NULL);
	pthread_mutex_init(arg.time_m, NULL);
	pthread_mutex_init(arg.philo_m, NULL);
	arg = init_philo(arg);
	loop_philo(&arg);
	free(arg.philo);
	return 1;
}

void	initialize_all(t_arg *all, t_arg *arg)
{
	int i;

	pthread_mutex_lock(arg->philo_m);
	i = *arg->current_philo;
	pthread_mutex_unlock(arg->philo_m);
	all->current_philo = malloc(sizeof(int));
	all->time = malloc(sizeof(unsigned long int));
	all->is_gone = malloc(sizeof(int));
	all->nb_philo = arg->nb_philo;
    all->nb_fork = arg->nb_fork;
    *all->current_philo = i;
    all->philo_dead = arg->philo_dead;
    all->time_to_die = arg->time_to_die;
   	all->current_time = arg->current_time;
    all->time_to_eat = arg->time_to_eat;
    all->time_to_sleep = arg->time_to_sleep;
	pthread_mutex_lock(arg->time_m);
	if (*arg->time == 0)
		*arg->time = actual_time();
	pthread_mutex_unlock(arg->time_m);
	all->lst_eat = 0;
	all->is_gone = arg->is_gone;
	all->time = arg->time;
	all->have_eat = 0;
	all->time_each_philo_must_eat = arg->time_each_philo_must_eat;
	all->write = arg->write;
	all->philo = arg->philo;
	pthread_mutex_init(&all->eat, NULL);
}