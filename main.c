#include "philo.h"

int mail = 0;   

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void    print_philo(t_philo philo)
{
    printf("----------------------------\n");
    printf("| philo.time_to_eat = %d\n", philo.time_to_eat);
    printf("| philo.time_to_die = %u\n", philo.time_to_die);
    printf("| philo.time_to_sleep = %d\n", philo.time_to_sleep);
    printf("| philo.nb_philo = %d\n", philo.nb_philo);
    printf("| philo.nb_fork = %d\n", philo.nb_fork);
    printf("| philo.time = %lu\n", philo.time);
    printf("----------------------------\n");
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    printf("%lu, philo %d is eating\n",philo->time, philo->current_philo);
    usleep(philo->time_to_eat * 1000);
    philo->time = philo->time + philo->time_to_eat;
    printf("%lu, philo %d is sleeping\n",philo->time, philo->current_philo);
    usleep(philo->time_to_sleep * 1000);
    philo->time = philo->time + philo->time_to_sleep;
    return NULL;
}

void    *is_dead(void *arg)
{
    int i = 0;
    t_philo *philo = (t_philo *)arg;

    usleep(philo->time_to_die * 1000);
    if (philo->philo_dead == 1)
    {
        printf("philo %d is dead\n", philo->current_philo);
        exit(EXIT_FAILURE);
    }
    return NULL;
}

int loop_philo(t_philo philo)
{   
    int i;
    struct timeval start;
    struct timeval end;
    
    i = 1;
    while (1)
    {
        philo.current_philo = i;
        gettimeofday(&start, NULL);
        if (pthread_create(&philo.philosopher[i], NULL, &routine, &philo) != 0)
            exit(EXIT_FAILURE);
        if (pthread_join(philo.philosopher[i], NULL) != 0)
            exit(EXIT_FAILURE);
        i++;
        if (i == philo.nb_philo)
            i = 0;
    }
    return 1;
}

int init_philo_struct(char **argv)
{   
    t_philo philo;
    struct timeval start;

    philo.time = 0;
    philo.nb_philo = ft_atoi(argv[1]);
    philo.nb_fork = ft_atoi(argv[1]);
    philo.time_to_die = ft_atoi(argv[2]);
    philo.time_to_eat = ft_atoi(argv[3]);
    philo.time_to_sleep = ft_atoi(argv[4]);
    philo.philo_dead = 0;
    pthread_mutex_init(&philo.fork, NULL);
    philo.philosopher = malloc(sizeof(pthread_t) * (philo.nb_philo + 1));
    print_philo(philo);
    loop_philo(philo);
    free(philo.philosopher);
    return 1;
}

int main(int argc, char **argv)
{
    t_philo philo;
    
    struct timeval start;
    struct timeval end;
    if (argc != 5)
    {
        exit(EXIT_FAILURE);
    }
    init_philo_struct(argv);
    pthread_mutex_destroy(&philo.fork);
    int time = (end.tv_usec / 1000) - (start.tv_usec / 1000);
    return 0;
}
