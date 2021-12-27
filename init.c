/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:46:45 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/27 10:57:01 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_arg	init_philo(t_arg arg)
{
	int	i;

	i = 1;
	arg.philo = malloc(sizeof(t_philo) * (arg.nb_fork));
	while (i <= arg.nb_fork)
	{
		pthread_mutex_init(&arg.philo[i - 1].fork, NULL);
		i++;
	}
	return (arg);
}

t_arg	init_philo_struct2(t_arg arg, char **argv)
{
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	*arg.finish_eat = 0;
	*arg.current_philo = 1;
	*arg.philo_dead = 0;
	*arg.time = 0;
	pthread_mutex_init(arg.write, NULL);
	pthread_mutex_init(arg.time_m, NULL);
	pthread_mutex_init(arg.philo_m, NULL);
	return (arg);
}

void	free_arg(t_arg arg)
{
	int	i;

	i = 0;
	ft_usleep(arg.time_to_die + 15);
	pthread_mutex_destroy(arg.time_m);
	while (i < arg.nb_fork)
	{
		pthread_mutex_destroy(&arg.philo[i].fork);
		i++;
	}
	free(arg.philo);
	free(arg.time_m);
	free(arg.time);
	free(arg.philo_dead);
	free(arg.current_philo);
	free(arg.finish_eat);
	free(arg.write);
	pthread_mutex_lock(arg.philo_m);
	usleep(100);
	pthread_mutex_unlock(arg.philo_m);
	pthread_mutex_destroy(arg.philo_m);
	free(arg.philo_m);
}

int	init_philo_struct(char **argv, int argc)
{
	t_arg	arg;

	arg.temp = 0;
	arg = verif_arg(arg, argc, argv);
	arg.nb_fork = ft_atoi(argv[1]);
	arg.time = malloc(sizeof(unsigned long int) * arg.nb_fork);
	arg.write = malloc(sizeof(pthread_mutex_t) * arg.nb_fork);
	arg.time_m = malloc(sizeof(pthread_mutex_t) * arg.nb_fork);
	arg.philo_m = malloc(sizeof(pthread_mutex_t) * 1);
	arg.finish_eat = malloc(sizeof(int) * arg.nb_fork);
	arg.current_philo = malloc(sizeof(int) * arg.nb_fork);
	arg.philo_dead = malloc(sizeof(int) * arg.nb_fork);
	arg = init_philo_struct2(arg, argv);
	arg = init_philo(arg);
	loop_philo(&arg);
	free_arg(arg);
	return (1);
}
