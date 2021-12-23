#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>


typedef struct s_philo{
    int nb_philo;
    int current_philo;
    unsigned long int last_eat;
    int philo_dead;
    int eat;
    pthread_mutex_t fork;
    pthread_t   philosopher;
    
}               t_philo;

typedef struct s_arg{
    int temp;
    int finish;
    int *finish_eat;
    int nb_philo;
    int nb_fork;
    int *current_philo;
    int philo_curr;
    int *philo_dead;
    unsigned long int time_to_die;
    int *is_gone;
    int have_eat;
    unsigned long int   lst_eat;
    unsigned long int   *time;
    unsigned long int current_time;
    int time_to_eat;
    int time_to_sleep;
    int time_each_philo_must_eat;
    pthread_mutex_t *write;
    pthread_mutex_t eat;
    pthread_mutex_t finish_m;
    pthread_mutex_t *time_m;
    pthread_mutex_t *philo_m;
    t_philo     *philo;
    t_philo     *philo_all;
}               t_arg;

int ft_atoi(char *str);
long int		actual_time(void);
void	ft_usleep(long int time_in_ms);
void	is_eat(t_arg *arg);
void 	is_sleep_and_think(t_arg *all);
void    *is_dead(void *arg);
t_arg   init_philo(t_arg arg);
int init_philo_struct(char **argv, int argc);
void	initialize_all(t_arg *all, t_arg *arg);
int loop_philo(t_arg *arg_temp);

#endif