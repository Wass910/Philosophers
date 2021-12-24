/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idhiba <idhiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 20:13:09 by idhiba            #+#    #+#             */
/*   Updated: 2021/12/24 20:21:10 by idhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo{
	pthread_mutex_t	fork;
	pthread_t		philosopher;	
}				t_philo;

typedef struct s_arg{
	int					temp;
	int					finish;
	int					*finish_eat;
	int					nb_philo;
	int					nb_fork;
	int					*current_philo;
	int					philo_curr;
	int					*philo_dead;
	unsigned long int	time_to_die;
	int					have_eat;
	unsigned long int	lst_eat;
	unsigned long int	*time;
	unsigned long int	current_time;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_each_philo_must_eat;
	pthread_mutex_t		*write;
	pthread_mutex_t		eat;
	pthread_mutex_t		finish_m;
	pthread_mutex_t		*time_m;
	pthread_mutex_t		*philo_m;
	pthread_mutex_t		clean_forks;
	t_philo				*philo;
}				t_arg;

int			ft_atoi(char *str);
long int	actual_time(void);
void		ft_usleep(long int time_in_ms);
void		is_eat(t_arg *arg);
void		is_sleep_and_think(t_arg *all);
void		*is_dead(void *arg);
t_arg		init_philo(t_arg arg);
int			init_philo_struct(char **argv, int argc);
void		initialize_all(t_arg *all, t_arg *arg);
int			loop_philo(t_arg *arg_temp);
int			init_next_philo(t_arg all);
t_arg		init_finish(t_arg all);
int			one_philo(t_arg all);

#endif