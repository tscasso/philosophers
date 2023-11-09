/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:43:44 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/09 15:56:25 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

# define ARGS_ERROR 1
# define ARGS_NUM_ERROR 2

typedef struct s_sim
{
	int				nb_philo;
	int				max_eat;
	int				philo_ate;
	int				eat_time;
	int				sleep_time;
	int				stop_sim;
	size_t			die_timeout;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_lock;
	pthread_mutex_t	check_lock;
	pthread_mutex_t	nb_ate_lock;
	pthread_mutex_t	death_check_lock;
}		t_sim;

/* Philosophers */

typedef struct s_philo
{
	pthread_t		thread;
	t_sim			*sim;
	size_t			start_time;
	size_t			last_meal;
	int				philo_id;
	int				nb_eat;
	int				l_fork;
	int				r_fork;
	short			is_finished;
}		t_philo;

/* Parsing */

int		check_args(char **av);
int		ft_is_digit(char *c);

/* Initialization */

t_philo	**init_philo(t_sim *sim);
t_sim	*init_simulation(char **av);
void	init_mutex(t_sim *sim);

/* Routine */

void	*routine(void *ph);
void	*only_you(t_philo *philo);

/* Philo routines */

void	take_forks(t_philo *philo);
void	eat_time(t_philo *philo);
void	sleep_time(t_philo *philo);
void	think_time(t_philo *philo);
void	die_time(t_philo *philo);

/* Check functions */

void	init_death(t_philo *philo);
void	nb_eat_count(t_philo *philo);
void	timeof_last_meal(t_philo *philo);
int		check_death(t_philo *philo);
int		check_philo(t_philo **philo, t_sim *sim);
int		check_nb_eat(t_philo *philo);
size_t	check_meals(t_philo *philo);

/* error */

void	handle_error(short error_code);

/* Utils */

long	ft_atol(char *s);
size_t	get_time(void);
void	psleep(size_t ms);

#endif