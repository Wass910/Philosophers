/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:22:52 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/28 13:33:26 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	all_philo_eat(t_arg *philo)
{
	ft_usleep(philo->time_to_eat + philo->time_to_sleep + 50);
	sem_wait(philo->write);
	printf("Each philo ate %d time(s)\n", philo->time_each_philo_must_eat);
	exit(0);
}

int	day_philo(int count, t_arg *philo, unsigned long int time, sem_t *test)
{
	pthread_t	dead;

	philo->current_philo = count;
	philo->eat_s = test;
	philo->time = time;
	if (one_philo(philo) == 1)
		return (0);
	if (philo->current_philo % 2 == 0)
		ft_usleep(15);
	if (pthread_create(&dead, NULL, &is_dead, philo) != 0)
		exit(EXIT_FAILURE);
	pthread_detach(dead);
	while (1)
	{
		if (philo->have_eat == philo->time_each_philo_must_eat)
			all_philo_eat(philo);
		is_eating(philo);
		sem_wait(philo->eat_s);
		if (philo->time_each_philo_must_eat != -1)
			philo->have_eat++;
		sem_post(philo->eat_s);
		is_sleeping_and_thinking(philo);
	}
	return (1);
}

void	creat_process(t_arg philo, t_arg *all, t_start *start)
{
	philo = *all;
	usleep(100);
	start->pid[start->count] = fork();
	if (start->pid[start->count] == 0)
	{
		day_philo(start->count + 1, &philo, start->time, start->test);
		exit(1);
	}
	start->pid_temp[start->count] = start->pid[start->count];
	start->i++;
	start->count++;
}

int	start(t_arg *all)
{
	t_start	start;
	t_arg	philo;

	start.i = 0;
	init_start(&start, all);
	while (start.i < all->nb_fork)
		creat_process(philo, all, &start);
	start.i = 0;
	start.count = 0;
	while (start.i < all->nb_fork)
	{
		waitpid(-1, NULL, 0);
		while (start.count < all->nb_fork)
		{
			kill(start.pid_temp[start.count], SIGTERM);
			start.count++;
		}
		start.i++;
	}
	clean_prog(&start, all);
	return (1);
}

int	main(int argc, char **argv)
{
	sem_unlink("pforks");
	sem_unlink("pwrite");
	sem_unlink("pdead");
	sem_unlink("peat_s");
	sem_unlink("ptest");
	init_arg(argc, argv);
	sem_unlink("pforks");
	sem_unlink("pwrite");
	sem_unlink("pdead");
	sem_unlink("peat_s");
	sem_unlink("ptest");
	return (0);
}
