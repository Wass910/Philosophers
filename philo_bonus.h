/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:01:19 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/28 13:53:35 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_star{
	pid_t				*pid;
	pid_t				*pid_temp;
	int					i;
	sem_t				*test;
	int					count;
	unsigned long int	time;
}				t_start;

typedef struct s_arg{
	int					*temp;
	int					finish;
	int					nb_fork;
	int					current_philo;
	int					philo_dead;
	unsigned long int	time_to_die;
	int					have_eat;
	unsigned long int	lst_eat;
	unsigned long int	time;
	unsigned long int	current_time;
	int					time_to_eat;
	int					time_to_sleep;
	sem_t				*p_forks;
	sem_t				*write;
	sem_t				*dead_s;
	sem_t				*eat_s;
	int					time_each_philo_must_eat;
}				t_arg;

int			ft_atoi(char *str);
long int	actual_time(void);
void		ft_usleep(long int time_in_ms);
int			one_philo(t_arg *philo);
void		writting_eat(t_arg *philo);
void		is_eating(t_arg *philo);
void		is_sleeping_and_thinking(t_arg *philo);
void		*is_dead(void *arg);
void		init_arg(int argc, char **argv);
int			start(t_arg *all);
void		clean_prog(t_start *start, t_arg *all);
void		init_start(t_start *start, t_arg *all);

#endif