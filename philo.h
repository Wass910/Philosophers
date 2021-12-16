#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_philo{
    int nb_philo;
    int current_philo;
    unsigned long int last_eat;
    int philo_dead;
    pthread_mutex_t fork;
    pthread_mutex_t next_fork;
    pthread_mutex_t is_dead;
    pthread_t   philosopher;
    
}               t_philo;

typedef struct s_arg{
    int nb_philo;
    int nb_fork;
    int *current_philo;
    int philo_dead;
    int time_to_die;
    unsigned long int time;
    unsigned long int current_time;
    int time_to_eat;
    int time_to_sleep;
    int time_each_philo_must_eat;
    t_philo     *philo;
    t_philo     *philo_all;
}               t_arg;

int ft_atoi(char *str);

#endif