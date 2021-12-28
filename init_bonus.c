/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:37:38 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/28 13:12:03 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_arg(int argc, char **argv)
{
	t_arg	all;

	all.nb_fork = ft_atoi(argv[1]);
	all.time_to_die = ft_atoi(argv[2]);
	all.time_to_eat = ft_atoi(argv[3]);
	all.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		all.time_each_philo_must_eat = ft_atoi(argv[5]);
	else
		all.time_each_philo_must_eat = -1;
	all.lst_eat = 0;
	all.have_eat = 0;
	all.philo_dead = 0;
	all.p_forks = sem_open("pforks", O_CREAT, 0644, all.nb_fork);
	all.write = sem_open("pwrite", O_CREAT, 0644, 1);
	all.dead_s = sem_open("pdead", O_CREAT, 0644, 1);
	if (all.p_forks == SEM_FAILED || all.write == SEM_FAILED
		|| all.dead_s == SEM_FAILED)
	{
		printf("fail with semaphore\n");
		exit(EXIT_FAILURE);
	}
	start(&all);
}

void	clean_prog(t_start *start, t_arg *all)
{
	sem_close(all->write);
	sem_close(all->p_forks);
	sem_close(all->dead_s);
	sem_close(start->test);
	free(start->pid);
	free(start->pid_temp);
}

void	init_start(t_start *start, t_arg *all)
{
	start->count = 0;
	start->test = sem_open("ptest", O_CREAT, 0644, 1);
	start->pid_temp = malloc(sizeof(pid_t) * (all->nb_fork + 1));
	start->pid = malloc(sizeof(pid_t) * all->nb_fork);
	start->time = actual_time();
}
