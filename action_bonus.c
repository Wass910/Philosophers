/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:27:08 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/28 13:11:41 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	writting_eat(t_arg *philo)
{
	printf("%lu, philo %d is taken a fork\n",
		(philo->current_time - philo->time), philo->current_philo);
	printf("%lu, philo %d is eating\n",
		(philo->current_time - philo->time), philo->current_philo);
}

void	is_eating(t_arg *philo)
{
	sem_wait(philo->p_forks);
	sem_wait(philo->write);
	philo->current_time = actual_time();
	sem_wait(philo->dead_s);
	if (philo->philo_dead != 1)
		printf("%lu, philo %d is taken a fork1\n",
			(philo->current_time - philo->time), philo->current_philo);
	sem_post(philo->dead_s);
	sem_post(philo->write);
	sem_wait(philo->p_forks);
	sem_wait(philo->write);
	sem_wait(philo->dead_s);
	philo->current_time = actual_time();
	if (philo->philo_dead != 1)
		writting_eat(philo);
	sem_post(philo->dead_s);
	sem_wait(philo->eat_s);
	philo->lst_eat = (philo->current_time - philo->time);
	sem_post(philo->eat_s);
	sem_post(philo->write);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->p_forks);
	sem_post(philo->p_forks);
}

void	is_sleeping_and_thinking(t_arg *philo)
{
	philo->current_time = actual_time();
	sem_wait(philo->write);
	sem_wait(philo->dead_s);
	philo->current_time = actual_time();
	if (philo->philo_dead != 1)
		printf("%lu, philo %d is sleeping\n",
			(philo->current_time - philo->time), philo->current_philo);
	sem_post(philo->dead_s);
	sem_post(philo->write);
	ft_usleep(philo->time_to_sleep);
	philo->current_time = actual_time();
	sem_wait(philo->write);
	sem_wait(philo->dead_s);
	if (philo->philo_dead != 1)
		printf("%lu, philo %d is thinkig\n",
			(philo->current_time - philo->time), philo->current_philo);
	sem_post(philo->dead_s);
	sem_post(philo->write);
}

void	*is_dead(void *arg)
{
	t_arg				*all;
	unsigned long int	curr_time;
	unsigned long int	launch_time;

	all = (t_arg *)arg;
	launch_time = all->time;
	while (1)
	{
		usleep(10);
		curr_time = actual_time();
		sem_wait(all->eat_s);
		if ((curr_time - launch_time) > all->lst_eat
			&& all->have_eat != all->time_each_philo_must_eat
			&& ((curr_time - launch_time) - all->lst_eat) > all->time_to_die)
		{
			sem_wait(all->write);
			printf("%lu, philo %d is dead\n",
				(curr_time - launch_time), all->current_philo);
			exit(1);
		}
		sem_post(all->eat_s);
	}
}
