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

// void    print_philo(t_philo philo)
// {
//     printf("----------------------------\n");
//     printf("| philo.time_to_eat = %d\n", philo.time_to_eat);
//     printf("| philo.time_to_die = %u\n", philo.time_to_die);
//     printf("| philo.time_to_sleep = %d\n", philo.time_to_sleep);
//     printf("| philo.nb_philo = %d\n", philo.nb_philo);
//     printf("| philo.nb_fork = %d\n", philo.nb_fork);
//     printf("| philo.time = %lu\n", philo.time);
//     printf("----------------------------\n");
// }

void    print_arg(t_arg arg)
{
	printf("----------------------------\n");
	printf("| arg.time_to_eat = %d\n", arg.time_to_eat);
	printf("| arg.time_to_die = %u\n", arg.time_to_die);
	printf("| arg.time_to_sleep = %d\n", arg.time_to_sleep);
	printf("| arg.time = %lu\n", arg.time);
	printf("----------------------------\n");
}

// void    *routine(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg;
// 	struct timeval start;
// 	struct timeval end;


// 	if (philo->time == 0)
// 		philo->time = actual_time();
//     pthread_mutex_lock(philo->fork);
// 	philo->current_time = actual_time();
// 	printf("%lu, philo %d is eating\n",(philo->current_time - philo->time), philo->current_philo);
// 	usleep(philo->time_to_eat * 1000);
// 	philo->current_time = actual_time();
// 	printf("%lu, philo %d is sleeping\n", (philo->current_time - philo->time), philo->current_philo);
// 	usleep(philo->time_to_sleep * 1000);
//     pthread_mutex_unlock(philo->fork);
// 	return NULL;
// }

// void    *is_dead(void *arg)
// {
//     int i = 0;
//     t_philo *philo = (t_philo *)arg;

//     usleep(philo->time_to_die * 1000);
//     if (philo->philo_dead == 1)
//     {
//         printf("philo %d is dead\n", philo->current_philo);
//         exit(EXIT_FAILURE);
//     }
//     return NULL;
// }

// int loop_philo(t_philo philo)
// {   
//     int i;
//     struct timeval start;
//     struct timeval end;
    
//     i = 1;
//     while (1)
//     {
//         philo.current_philo = i;
//         if (pthread_create(&philo.philosopher[i - 1], NULL, &routine, &philo) != 0)
//             exit(EXIT_FAILURE);
//         // if (pthread_join(philo.philosopher[i - 1], NULL) != 0)
//         //     exit(EXIT_FAILURE);
//         if (i == philo.nb_philo)
//             i = 0;
//         i++;
//     }
//     return 1;
// }

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
    print_arg(arg);
    arg = init_philo(arg);
    //loop_philo(philo);
    //free(philo.philosopher);
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
